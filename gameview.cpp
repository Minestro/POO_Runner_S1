#include "gameview.h"
#include <iostream>

GameView::GameView(): m_gameModel{nullptr}
{

}


void GameView::insertGraphicElementIntoList(GraphicElement *ge)
{
    std::vector<const GraphicElement*>::iterator it = m_drawableElementsList.begin();
    while(it != m_drawableElementsList.end() && **it < *ge)
    {
        ++it;
    }
    m_drawableElementsList.insert(it, ge);
}

bool GameView::treatEvent()
{
    bool quitter = false;
    std::vector<std::pair<bool, GameCharacter*> >::iterator player1 = m_gameModel->getCharacters().begin();
    while (player1 != m_gameModel->getCharacters().end() && player1->second->getId() != 0)
    {
        ++player1;
    }
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
                if (player1 != m_gameModel->getCharacters().end())
                {
                    player1->second->rightMove(1);
                }
                break;
            case sf::Keyboard::Left :
                if (player1 != m_gameModel->getCharacters().end())
                {
                    player1->second->leftMove(1);
                }
                break;
            case sf::Keyboard::Up :
                if (player1 != m_gameModel->getCharacters().end())
                {
                    player1->second->jump();
                }
            break;
            case sf::Keyboard::A :
                m_gameModel->getCharacters()[0].second->addScore(100);
                break;
            default:
                break;
            }
            break;
        case sf::Event::KeyReleased :
            switch (m_window->getEvent()->key.code) {
            case sf::Keyboard::Left:
                if (player1 != m_gameModel->getCharacters().end())
                {
                    player1->second->leftMove(0);
                }
                break;
            case sf::Keyboard::Right:
                if (player1 != m_gameModel->getCharacters().end())
                {
                    player1->second->rightMove(0);
                }
                break;
            case sf::Event::MouseMoved:
                m_gameModel->setCursorPosition(m_window->mapPixelToCoords(sf::Vector2i{sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y}).x, m_window->mapPixelToCoords(sf::Vector2i{sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y}).y);
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
    std::vector <const GraphicElement*>::const_iterator iterator = m_drawableElementsList.begin();
    while (iterator != m_drawableElementsList.end())
    {
        (**iterator).draw(m_window);
        ++iterator;
    }
    m_window->display();
}

void GameView::synchronise()
{
    //Si le gameModel contient des nouveaux élements on les ajoutes à la liste elementToGraphicElement en lui associant un ou plusieurs GraphicElement
    for (unsigned int i=0; i<m_gameModel->getCharacters().size(); i++)
    {
        if (m_gameModel->getCharacters()[i].first)
        {
            std::map <const Element*, std::list<GraphicElement*> >::const_iterator it = m_elementToGraphicElement.find(m_gameModel->getCharacters()[i].second);
            if (it == m_elementToGraphicElement.end())
            {
                std::list<GraphicElement*> list;
                list.push_back(new GameCharacterGraphic{10, m_gameModel->getCharacters()[i].second->getSize().first, m_gameModel->getCharacters()[i].second->getSize().second, m_gameModel->getCharacters()[i].second->getPosition().first, m_gameModel->getCharacters()[i].second->getPosition().second, GraphicElement::m_listTextures["character.png"], 1, 8, 1, 1, 100});
                list.push_back(new LifeBar{100, 200, 30, 1000, 600, 20});
                list.push_back(new ScoreGraphic{100, 50, 600, TextElement::m_listFonts["score.ttf"], 20, 5, sf::Color::White});
                m_elementToGraphicElement.insert(std::make_pair(m_gameModel->getCharacters()[i].second, list));
            } else {

            }
            m_gameModel->getCharacters()[i].first = 0;
        }
    }

    for (unsigned int i=0; i<m_gameModel->getObstacles().size(); i++)
    {
        if (m_gameModel->getObstacles()[i].first)
        {
            std::map <const Element*, std::list<GraphicElement*> >::const_iterator it = m_elementToGraphicElement.find(m_gameModel->getObstacles()[i].second);
            if (it == m_elementToGraphicElement.end())
            {
                std::list<GraphicElement*> list;
                list.push_back(new SpriteElement{10, m_gameModel->getObstacles()[i].second->getSize().first, m_gameModel->getObstacles()[i].second->getSize().second, m_gameModel->getObstacles()[i].second->getPosition().first, m_gameModel->getObstacles()[i].second->getPosition().second, GraphicElement::m_listTextures["obstacles_block.png"], 1, 2, 1, 1, 1, 100});
                m_elementToGraphicElement.insert(std::make_pair(m_gameModel->getObstacles()[i].second, list));
            } else {

            }
            m_gameModel->getObstacles()[i].first = 0;
        }
    }

    for (unsigned int i=0; i<m_gameModel->getBackgrounds().size(); i++)
    {
        if (m_gameModel->getBackgrounds()[i].first)
        {
            std::map <const Element*, std::list<GraphicElement*> >::const_iterator it = m_elementToGraphicElement.find(m_gameModel->getBackgrounds()[i].second);
            if (it == m_elementToGraphicElement.end())
            {
                std::list<GraphicElement*> list;
                if (m_gameModel->getBackgrounds()[i].second->isSliding())
                {
                    sf::Texture *texture = GraphicElement::m_listTextures[m_gameModel->getBackgrounds()[i].second->getBackgroundFileName()];
                    texture->setRepeated(1);
                    SpriteElement *ge = new SpriteElement{(unsigned int)m_gameModel->getBackgrounds()[i].second->getZIndex(), m_gameModel->getBackgrounds()[i].second->getSize().first, m_gameModel->getBackgrounds()[i].second->getSize().second, m_gameModel->getBackgrounds()[i].second->getPosition().first, m_gameModel->getBackgrounds()[i].second->getPosition().second, texture};
                    ge->setTextureRect(sf::IntRect{ge->getTextureRect().left, ge->getTextureRect().top, ge->getTextureRect().width*2, ge->getTextureRect().height});
                    list.push_back(ge);
                    m_elementToGraphicElement.insert(std::make_pair(m_gameModel->getBackgrounds()[i].second, list));
                } else {
                    list.push_back(new SpriteElement{(unsigned int)m_gameModel->getBackgrounds()[i].second->getZIndex(), m_gameModel->getBackgrounds()[i].second->getSize().first, m_gameModel->getBackgrounds()[i].second->getSize().second, m_gameModel->getBackgrounds()[i].second->getPosition().first, m_gameModel->getBackgrounds()[i].second->getPosition().second, GraphicElement::m_listTextures[m_gameModel->getBackgrounds()[i].second->getBackgroundFileName()]});
                    m_elementToGraphicElement.insert(std::make_pair(m_gameModel->getBackgrounds()[i].second, list));
                }
            } else {

            }
            m_gameModel->getBackgrounds()[i].first = 0;
        }
    }

    //Pareil mais si des élements ont été supprimés
    if (m_gameModel->getDeletedElements().size() > 0)
    {
        std::vector<const Element*>::const_iterator deletedElement = m_gameModel->getDeletedElements().begin();
        std::map <const Element*, std::list<GraphicElement*> >::const_iterator it;
        while (deletedElement != m_gameModel->getDeletedElements().end())
        {
            it = m_elementToGraphicElement.find(*deletedElement);
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
            ++deletedElement;
        }
        m_gameModel->getDeletedElements().clear();
    }

    //Une fois que l'on a mis à jour notre tableau de correspondance elementToGraphicElement on met à jour leurs positions et leurs tailles
    std::map <const Element*, std::list<GraphicElement*> >::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        std::list<GraphicElement*>::const_iterator iterator2 = iterator->second.begin();
        while (iterator2 != iterator->second.end())
        {
            (**iterator2).refresh(iterator->first, m_gameModel);
            ++iterator2;
        }
        ++iterator;
    }

}

void GameView::fillGraphicElementsList()
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

