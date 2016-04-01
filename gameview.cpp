#include "gameview.h"
#include <iostream>

GameView::GameView()
{

}

bool GameView::treatEvent()
{
    bool quitter = false;
    while (m_window->pollEvent(*m_window->getEvent()))
    {
        switch (m_window->getEvent()->type)
        {
        case sf::Event::Closed :
            m_window->close();
            quitter = true;
            break;
        case sf::Event::Resized :
            synchronise();
            break;
        case sf::Event::KeyPressed :
            switch (m_window->getEvent()->key.code)
            {
            case sf::Keyboard::Right :
                m_gameModel->getCharacter()->rightMove(1);
                break;
            case sf::Keyboard::Left :
                m_gameModel->getCharacter()->leftMove(1);
                break;
            case sf::Keyboard::Up :
                m_gameModel->getCharacter()->jump();
            break;
            default:
                break;
            }
            break;
        case sf::Event::KeyReleased :
            switch (m_window->getEvent()->key.code) {
            case sf::Keyboard::Left:
                m_gameModel->getCharacter()->leftMove(0);
                break;
            case sf::Keyboard::Right:
                m_gameModel->getCharacter()->rightMove(0);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    return quitter;
}

void GameView::setModel(Game *model)
{
    m_gameModel = model;
}

void GameView::setWindow(Window *window)
{
    m_window = window;
}

void GameView::draw()
{
    m_window->clear();
    fillGraphicElementsList();
    std::set <const GraphicElement*>::const_iterator iterator = m_graphicElementsList.begin();
    while (iterator != m_graphicElementsList.end())
    {
        m_window->draw(**iterator);
        ++iterator;
    }
    m_window->display();
}

void GameView::synchronise()
{
    //Si le gameModel contient des nouveaux élements on les ajoutes à la liste elementToGraphicElement en lui associant un GraphicElement
    if (m_gameModel->getNewElements().size() > 0)
    {
        std::vector<const Element*>::const_iterator iterator = m_gameModel->getNewElements().begin();
        while (iterator != m_gameModel->getNewElements().end())
        {
            std::string className = (**iterator).getClassName();
            if (className == "GameCharacter")
            {
                m_elementToGraphicElement.insert(std::make_pair(*iterator, new AnimableElement{10, 1, 8, (**iterator).getSize().first, (**iterator).getSize().second, (**iterator).getPosition().first, (**iterator).getPosition().second, GraphicElement::m_listTextures["character.png"], 100}));
            } else if (className == "Obstacle")
            {
                m_elementToGraphicElement.insert(std::make_pair(*iterator, new AnimableElement{10, 1, 1, (**iterator).getSize().first, (**iterator).getSize().second, (**iterator).getPosition().first, (**iterator).getPosition().second, GraphicElement::m_listTextures["obstacles.png"], 100}));
            } else if (className == "Background")
            {
                const Background *bckg = dynamic_cast<const Background*>(*iterator);
                if (bckg->isSliding())
                {
                    sf::Texture *texture = GraphicElement::m_listTextures[bckg->getBackgroundFileName()];
                    texture->setRepeated(1);
                    SimpleGraphicElement *ge = new SimpleGraphicElement{0, bckg->getSize().first, bckg->getSize().second, bckg->getPosition().first, bckg->getPosition().second, texture};
                    m_elementToGraphicElement.insert(std::make_pair(*iterator, ge));
                    ge->setTextureRect(sf::IntRect{ge->getTextureRect().left, ge->getTextureRect().top, ge->getTextureRect().width * 2, ge->getTextureRect().height});
                } else {
                    m_elementToGraphicElement.insert(std::make_pair(*iterator, new SimpleGraphicElement{0, bckg->getSize().first, bckg->getSize().second, bckg->getPosition().first, bckg->getPosition().second, GraphicElement::m_listTextures[bckg->getBackgroundFileName()]}));
                }
            } else {

            }
            ++iterator;
        }
        m_gameModel->getNewElements().clear();
    }

    //Pareil mais si des élements ont été supprimés
    if (m_gameModel->getDeletedElements().size() > 0)
    {
        std::vector<const Element*>::const_iterator iterator = m_gameModel->getDeletedElements().begin();
        std::map <const Element*, GraphicElement*>::const_iterator it;
        while (iterator != m_gameModel->getDeletedElements().end())
        {
            it = m_elementToGraphicElement.find(*iterator);
            if (it != m_elementToGraphicElement.end())
            {
                delete it->second;
                m_elementToGraphicElement.erase(it);
            }
            ++iterator;;
        }
        m_gameModel->getDeletedElements().clear();
    }

    //Une fois que l'on a mis à jour notre tableau de correspondance elementToGraphicElement on met à jour leurs positions et leurs tailles
    std::map <const Element*, GraphicElement*>::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        iterator->second->setSize(iterator->first->getSize().first, iterator->first->getSize().second);
        iterator->second->setPosition(iterator->first->getPosition().first, iterator->first->getPosition().second);
        if (iterator->second->getClassName() == "AnimableElement")
        {
            AnimableElement *elem = dynamic_cast<AnimableElement*>(iterator->second);
            elem->animate();
        }
        ++iterator;
    }
}

void GameView::fillGraphicElementsList()
{
    //Cette fonction ajoute dans un set tous les graphicElements du tableau de correspondance elementToGraphicElement et qui seront triés suivant leur z-index
    m_graphicElementsList.clear();
    std::map <const Element*, GraphicElement*>::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        m_graphicElementsList.insert(iterator->second);
        ++iterator;
    }
}

bool compGraphicElement::operator ()(const GraphicElement *g1, const GraphicElement *g2) const
{
    {
        return (*g1)<(*g2);
    }
}
