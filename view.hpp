#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>
#include "menu.h"
#include "game.h"
#include "window.h"
#include "spriteelement.h"
#include "circleshapeelement.h"
#include "rectangleshapeelement.h"
#include "lifebar.h"
#include "textelement.h"
#include "gamecharactergraphic.h"
#include "scoregraphic.h"
#include "buttongraphic.h"

template<typename ModelT>
class View
{
protected:
    ModelT *m_model;
    std::map <const Element*, std::list<GraphicElement*> > m_elementToGraphicElement;
    std::vector <const GraphicElement*> m_drawableElementsList;
    std::map<unsigned int, sf::Shader*> m_layeredShader;
    Window *m_window;

    void insertGraphicElementIntoList(GraphicElement *ge)
    {
        std::vector<const GraphicElement*>::iterator it = m_drawableElementsList.begin();
        while(it != m_drawableElementsList.end() && **it < *ge)
        {
            ++it;
        }
        m_drawableElementsList.insert(it, ge);
    }

    void fillGraphicElementsList()
    {
        //Cette fonction ajoute dans une liste de tous les graphicElements du tableau de correspondance elementToGraphicElement et qui seront triés suivant leur z-index
        m_drawableElementsList.clear();
        std::map <const Element*, std::list <GraphicElement*> >::const_iterator iterator = m_elementToGraphicElement.begin();
        while(iterator != m_elementToGraphicElement.end())
        {
            std::list<GraphicElement*>::const_iterator iterator2 = iterator->second.begin();
            while(iterator2 != iterator->second.end())
            {
                insertGraphicElementIntoList(*iterator2);
                ++iterator2;
            }
            ++iterator;
        }
    }

public:
    View():m_model{nullptr}
    {

    }
    virtual ~View()
    {
        std::map<const Element*, std::list<GraphicElement *> >::iterator map = m_elementToGraphicElement.begin();
        while (map != m_elementToGraphicElement.end())
        {
            std::list<GraphicElement *>::iterator list = map->second.begin();
            while (list != map->second.end())
            {
                delete *list;
                ++list;
            }
            ++map;
        }
    }

    void addLayeredShader(sf::Shader *shader, unsigned int zIndex)
    {
        if (m_layeredShader.find(zIndex) == m_layeredShader.end())
        {
            m_layeredShader.insert(std::make_pair(zIndex, shader));
        }
    }

    void removeLayeredShader(unsigned int zIndex)
    {
        std::map<unsigned int, sf::Shader*>::iterator it = m_layeredShader.find(zIndex);
        if (it != m_layeredShader.end())
        {
            m_layeredShader.erase(it);
        }
    }

    sf::Shader *getLayeredShader(unsigned int zIndex)
    {
        if (m_layeredShader.find(zIndex) != m_layeredShader.end())
        {
            return m_layeredShader[zIndex];
        } else {
            return nullptr;
        }
    }

    void draw()
    {
        m_window->clear();
        fillGraphicElementsList();
        unsigned int actualZIndex = 0;
        std::vector<sf::RenderTexture*> renderPart;
        for (unsigned int i = 0; i<m_layeredShader.size(); i++)
        {
            renderPart.push_back(new sf::RenderTexture);
            renderPart[i]->create(MODEL_SIZE_W, MODEL_SIZE_H);
            renderPart[i]->clear(sf::Color::Transparent);
        }
        unsigned int i = 0;
        for (std::pair<unsigned int, sf::Shader*> shader : m_layeredShader)
        {
            while (actualZIndex < shader.first)
            {
                for (const GraphicElement* ge : m_drawableElementsList)
                {
                    if (ge->getZIndex() == actualZIndex)
                    {
                        ge->draw(renderPart[i]);
                    } else if (ge->getZIndex() > actualZIndex)
                    {
                        break;
                    }
                }
                actualZIndex++;
            }
            renderPart[i]->display();
            sf::RenderStates state{};
            state.shader = shader.second;
            if (i < m_layeredShader.size() - 1)
            {
                renderPart[i+1]->draw(sf::Sprite{renderPart[i]->getTexture()}, state);
            } else {
                m_window->draw(sf::Sprite{renderPart[i]->getTexture()}, state);
            }
            i++;
        }
        if (actualZIndex > (*(m_drawableElementsList.end()-1))->getZIndex())
        {
            actualZIndex = (*(m_drawableElementsList.end()-1))->getZIndex();
        }
        std::vector <const GraphicElement*>::const_iterator it = m_drawableElementsList.begin();
        while ((**it).getZIndex() < actualZIndex)
        {
            ++it;
        }
        while (it != m_drawableElementsList.end())
        {
            (**it).draw(m_window);
            ++it;
        }
        m_window->display();
        for (sf::RenderTexture* rt : renderPart)
        {
            delete rt;
        }
    }

    virtual bool treatEvent() = 0;
    void synchronise()
    {
        //Si le gameModel contient des nouveaux élements on les ajoutes à la liste elementToGraphicElement en lui associant un ou plusieurs GraphicElement

        for (std::pair<bool, GameCharacter*> character: m_model->getCharacters())
        {
            if (character.first)
            {
                if (m_elementToGraphicElement.find(character.second) == m_elementToGraphicElement.end())
                {
                    std::list<GraphicElement*> list;
                    list.push_back(new GameCharacterGraphic{5, character.second->getSize().first, character.second->getSize().second, character.second->getPosition().first, character.second->getPosition().second, character.second->getRotateAngle(), GraphicElement::m_listTextures["plane.png"], 1, 2, 1, 1, 50});
                    list.push_back(new LifeBar{HUD_Z_INDEX, 200, 30, 1000, 600, 0, 20});
                    list.push_back(new ScoreGraphic{HUD_Z_INDEX, 50, 600, 0, TextElement::m_listFonts["score.ttf"], 20, 5, sf::Color::White});
                    m_elementToGraphicElement.insert(std::make_pair(character.second, list));
                }
                character.first = 0;
            }
        }

        for (std::pair<bool, Obstacle*> obstacle : m_model->getObstacles())
        {
            if (obstacle.first)
            {
                if (m_elementToGraphicElement.find(obstacle.second) == m_elementToGraphicElement.end())
                {
                    std::list<GraphicElement*> list;
                    std::string texture;
                    unsigned int nbLignes, nbColonnes, animationPeriod;
                    nbLignes = nbColonnes = animationPeriod = 0;
                    switch (obstacle.second->getType())
                    {
                    case obstacle_type::MINE:
                        texture = "mine.png";
                        nbLignes = 1;
                        nbColonnes = 1;
                        animationPeriod = 100;
                        break;
                    default:
                        break;
                    }
                    list.push_back(new SpriteElement{5, obstacle.second->getSize().first, obstacle.second->getSize().second, obstacle.second->getPosition().first, obstacle.second->getPosition().second, obstacle.second->getRotateAngle(), GraphicElement::m_listTextures[texture], nbLignes, nbColonnes, 1, 1, 1, animationPeriod});
                    m_elementToGraphicElement.insert(std::make_pair(obstacle.second, list));
                }
                obstacle.first = 0;
            }
        }

        for (std::pair<bool, Bonus*> bonus : m_model->getBonus())
        {
            if (bonus.first)
            {
                if (m_elementToGraphicElement.find(bonus.second) == m_elementToGraphicElement.end())
                {
                    std::list<GraphicElement*> list;
                    std::string texture;
                    unsigned int nbLignes, nbColonnes, animationPeriod;
                    nbLignes = nbColonnes = animationPeriod = 0;
                    switch (bonus.second->getType())
                    {
                    case bonus_type::PIECE:
                        texture = "coin.png";
                        nbLignes = 1;
                        nbColonnes = 10;
                        animationPeriod = 100;
                        break;
                    case bonus_type::SOINS:
                        texture = "Soins.png";
                        nbLignes = 1;
                        nbColonnes = 2;
                        animationPeriod = 200;
                        break;
                    default:
                        break;
                    }
                    list.push_back(new SpriteElement{5, bonus.second->getSize().first, bonus.second->getSize().second, bonus.second->getPosition().first, bonus.second->getPosition().second, bonus.second->getRotateAngle(), GraphicElement::m_listTextures[texture], nbLignes, nbColonnes, 1, 1, 1, animationPeriod});
                    m_elementToGraphicElement.insert(std::make_pair(bonus.second, list));
                }
                bonus.first = 0;
            }
        }

        for (std::pair<bool, Image*> image: m_model->getImages())
        {
            if (image.first)
            {
                if (m_elementToGraphicElement.find(image.second) == m_elementToGraphicElement.end())
                {
                    std::list<GraphicElement*> list;
                    sf::Texture *texture = GraphicElement::m_listTextures[image.second->getBackgroundFileName()];
                    SpriteElement *se = new SpriteElement{(unsigned int)image.second->getZIndex(), image.second->getSize().first, image.second->getSize().second, image.second->getPosition().first, image.second->getPosition().second, image.second->getRotateAngle(), texture};
                    if (image.second->isSliding())
                    {
                        texture->setRepeated(1);
                        se->setTextureRect(sf::IntRect{se->getTextureRect().left, se->getTextureRect().top, se->getTextureRect().width * 2, se->getTextureRect().height});
                    }
                    list.push_back(se);
                    m_elementToGraphicElement.insert(std::make_pair(image.second, list));
                }
                image.first = 0;
            }
        }

        for (std::pair<bool, Text*> text : m_model->getTexts())
        {
            if (text.first)
            {
                if (m_elementToGraphicElement.find(text.second) == m_elementToGraphicElement.end())
                {
                    std::list<GraphicElement*> list;
                    list.push_back(new TextElement{15, text.second->getSize().first, text.second->getSize().second, text.second->getPosition().first, text.second->getPosition().second, text.second->getRotateAngle(), text.second->getText(), TextElement::m_listFonts[text.second->getFont()], text.second->getFontSize(), text.second->getAutoRescale(), text.second->getlineBreak(), sf::Color{(sf::Uint8)text.second->getColor().r, (sf::Uint8)text.second->getColor().g, (sf::Uint8)text.second->getColor().b, (sf::Uint8)text.second->getColor().a}, 0, text.second->getEffect(), text.second->getEffectPeriod()});
                    m_elementToGraphicElement.insert(std::make_pair(text.second, list));
                }
                text.first = 0;
            }
        }

        for (std::pair<bool, Button*> button : m_model->getButtons())
        {
            if (button.first)
            {
                if (m_elementToGraphicElement.find(button.second) == m_elementToGraphicElement.end())
                {
                    std::list<GraphicElement*> list;
                    std::string texture;
                    unsigned int nbLignes, nbColonnes;
                    switch (button.second->getType())
                    {
                    case button_type::TEXT_BUTTON:
                        texture = "buttons.png";
                        nbLignes = 1;
                        nbColonnes = 2;
                        break;
                    case button_type::RADIO_BUTTON:
                        texture = "radioButton.png";
                        nbLignes = 1;
                        nbColonnes = 2;
                        break;
                    default:
                        break;
                    }
                    list.push_back(new ButtonGraphic{15, button.second->getSize().first, button.second->getSize().second, button.second->getPosition().first, button.second->getPosition().second, button.second->getRotateAngle(), GraphicElement::m_listTextures[texture], nbLignes, nbColonnes, button.second->getText(), TextElement::m_listFonts["score.ttf"], 20, sf::Color::White});
                    m_elementToGraphicElement.insert(std::make_pair(button.second, list));
                }
                button.first = 0;
            }
        }

        //Pareil mais si des élements ont été supprimés
        if (m_model->getDeletedElements().size() > 0)
        {
            std::map <const Element*, std::list<GraphicElement*> >::const_iterator it;
            for (const Element *el : m_model->getDeletedElements())
            {
                it = m_elementToGraphicElement.find(el);
                if (it != m_elementToGraphicElement.end())
                {
                    std::list<GraphicElement*>::const_iterator it2 = it->second.begin();
                    while(it2 != it->second.end())
                    {
                        delete *it2;
                        ++it2;
                    }
                    delete it->first;
                    m_elementToGraphicElement.erase(it);
                }
            }
            m_model->getDeletedElements().clear();
        }

        //Une fois que l'on a mis à jour notre tableau de correspondance elementToGraphicElement on met à jour leurs positions et leurs tailles
        std::map <const Element*, std::list<GraphicElement*> >::const_iterator iterator = m_elementToGraphicElement.begin();
        while(iterator != m_elementToGraphicElement.end())
        {
            std::list<GraphicElement*>::const_iterator iterator2 = iterator->second.begin();
            while (iterator2 != iterator->second.end())
            {
                (**iterator2).refresh(iterator->first, m_model);
                ++iterator2;
            }
            ++iterator;
        }
    }

    void setModel(ModelT *model)
    {
        m_model = model;
    }

    void setWindow(Window *window)
    {
        m_window = window;
    }
};

#endif // VIEW_HPP
