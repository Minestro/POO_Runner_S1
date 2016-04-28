#include "gamecharactergraphic.h"
#include <iostream>

GameCharacterGraphic::GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, int animatePeriod): SpriteElement::SpriteElement{zIndex, width, height, x, y, texture, animatePeriod}
{
    m_shadow = new CircleShapeElement{zIndex, width, width/2, x, HAUTEUR_SOL - 10, sf::Color::Black};
}

GameCharacterGraphic::GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, int nbLignes, int nbColonnes, int activeLigne, int activeColonne, int animatePeriod): SpriteElement::SpriteElement{zIndex, width, height, x, y, texture, nbLignes, nbColonnes, activeLigne, activeColonne, 1, animatePeriod}
{
    m_shadow = new CircleShapeElement{zIndex, width, width/2, x, HAUTEUR_SOL - 10, sf::Color::Black};
}

GameCharacterGraphic::~GameCharacterGraphic()
{
    delete m_shadow;
}

void GameCharacterGraphic::draw(sf::RenderWindow *window) const
{
    //m_shadow->draw(window);
    SpriteElement::draw(window);
}

void GameCharacterGraphic::refresh(const Element *el, Model *model)
{
    setPosition(el->getPosition().first, el->getPosition().second);
    setSize(el->getSize().first, el->getSize().second);
    std::vector<std::pair<bool, GameCharacter*> >::iterator it = model->getCharacters().begin();
    while (it != model->getCharacters().end() && it->second != el)
    {
        ++it;
    }
    if (it != model->getCharacters().end())
    {
        if (it->second->getId() != character_state::DYING)
        {
            float vitesseBalle = model->getCharacterSpeed(it->second).first;
            if (vitesseBalle >= 0)
            {
                changeDirectionSprite(1);
            } else {
                changeDirectionSprite(0);
            }
            float perimetreBalle = PI * it->second->getSize().first;
            setAnimatePeriod(std::abs((1/(vitesseBalle/perimetreBalle))/getNbLignes())*500);
        }

        int sizeShadow = getSize().first - ((HAUTEUR_SOL + 10)-(el->getPosition().second + el->getSize().second));
        if (sizeShadow < 0)
        {
            sizeShadow = 0;
        }
        m_shadow->setSize(sizeShadow, sizeShadow);
        m_shadow->setPosition(10, HAUTEUR_SOL - 15);
        switch (it->second->getState())
        {
        case character_state::DYING:
            if (getTexture() != GraphicElement::m_listTextures["explosion.png"])
            {
                setTexture(* GraphicElement::m_listTextures["explosion.png"]);
                setNbLignes(1);
                setNbColonnes(81);
                setRectPos(1);
            }
            setAutoLoop(0);
            if (m_activeColonne == m_nbColonnes)
            {
                model->getDeletedElements().push_back(el);
                model->getCharacters().erase(it);
            }
            break;
        default:
            if (getTexture() != GraphicElement::m_listTextures["character.png"])
            {
                setTexture(* GraphicElement::m_listTextures["character.png"]);
                setNbLignes(1);
                setNbColonnes(8);
                setRectPos(1);
            }
            setAutoLoop(1);
            break;
        }
    }
    animate();
}
