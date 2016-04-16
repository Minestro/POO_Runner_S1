#include "gameview.h"
#include <iostream>

GameView::GameView()
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
    //Si le gameModel contient des nouveaux élements on les ajoutes à la liste elementToGraphicElement en lui associant un GraphicElement
    if (m_gameModel->getNewElements().size() > 0)
    {
        std::vector<const Element*>::const_iterator iterator = m_gameModel->getNewElements().begin();
        while (iterator != m_gameModel->getNewElements().end())
        {
            std::string className = (**iterator).getClassName();
            if (className == "GameCharacter")
            {
                std::list<GraphicElement*> list;
                list.push_back(new SpriteElement{10, (**iterator).getSize().first, (**iterator).getSize().second, (**iterator).getPosition().first, (**iterator).getPosition().second, GraphicElement::m_listTextures["character.png"], 100, 2, 8});
                list.push_back(new LifeBar{100, 200, 30, 1000, 600});
                m_elementToGraphicElement.insert(std::make_pair(*iterator, list));

            } else if (className == "Obstacle")
            {
                std::list<GraphicElement*> list;
                list.push_back(new SpriteElement{10, (**iterator).getSize().first, (**iterator).getSize().second, (**iterator).getPosition().first, (**iterator).getPosition().second, GraphicElement::m_listTextures["obstacles_block.png"], 100, 1, 2});
                m_elementToGraphicElement.insert(std::make_pair(*iterator, list));
            } else if (className == "Background")
            {
                const Background *bckg = dynamic_cast<const Background*>(*iterator);
                std::list<GraphicElement*> list;
                if (bckg->isSliding())
                {
                    sf::Texture *texture = GraphicElement::m_listTextures[bckg->getBackgroundFileName()];
                    texture->setRepeated(1);
                    SpriteElement *ge = new SpriteElement{(unsigned int)bckg->getZIndex(), bckg->getSize().first, bckg->getSize().second, bckg->getPosition().first, bckg->getPosition().second, texture};
                    ge->setTextureRect(sf::IntRect{ge->getTextureRect().left, ge->getTextureRect().top, ge->getTextureRect().width*2, ge->getTextureRect().height});
                    list.push_back(ge);
                    m_elementToGraphicElement.insert(std::make_pair(*iterator, list));
                } else {
                    list.push_back(new SpriteElement{(unsigned int)bckg->getZIndex(), bckg->getSize().first, bckg->getSize().second, bckg->getPosition().first, bckg->getPosition().second, GraphicElement::m_listTextures[bckg->getBackgroundFileName()]});
                    m_elementToGraphicElement.insert(std::make_pair(*iterator, list));
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
        if (iterator->first->getClassName() == "GameCharacter")
        {
            /*float vitesseBalle = iterator->first->getPixelSpeed().first - m_gameModel->getPixelSpeed();
            if (vitesseBalle >= 0)
            {
                iterator->second->setRectPos(1, iterator->second->getActiveColonne());
            } else {
                iterator->second->setRectPos(2, iterator->second->getActiveColonne());
            }
            float perimetreBalle = PI * iterator->first->getSize().first;
            iterator->second->setAnimatePeriod(std::abs((1/(vitesseBalle/perimetreBalle))/iterator->second->getNbLignes())*1000);*/
        }
        std::list<GraphicElement*>::const_iterator iterator2 = iterator->second.begin();
        while (iterator2 != iterator->second.end())
        {
            (**iterator2).refresh(iterator->first);
            ++iterator2;
        }
        ++iterator;
    }

}

void GameView::fillGraphicElementsList()
{
    //Cette fonction ajoute dans un set tous les graphicElements du tableau de correspondance elementToGraphicElement et qui seront triés suivant leur z-index
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

