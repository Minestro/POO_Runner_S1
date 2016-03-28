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
    std::pair<float, float> viewRatio;
    viewRatio.first = (m_window->getSize().x * 1.0) / (m_gameModel->getSize().first * 1.0);
    viewRatio.second = (m_window->getSize().y * 1.0) / (m_gameModel->getSize().second * 1.0);

    //Si le gameModel contient des nouveaux élements on les ajoutes à la liste elementToGraphicElement en lui associant un GraphicElement
    if (m_gameModel->getNewElements().size() > 0)
    {
        std::vector<const Element*>::const_iterator iterator = m_gameModel->getNewElements().begin();
        while (iterator != m_gameModel->getNewElements().end())
        {
            if ((**iterator).isAnimated())
            {

            } else {
                m_elementToGraphicElement.insert(std::make_pair(*iterator, new GraphicElement{(**iterator).getzIndex(), (**iterator).getSize().first * viewRatio.first, (**iterator).getSize().second * viewRatio.second, (**iterator).getPosition().first * viewRatio.first, (**iterator).getPosition().second * viewRatio.second, GraphicElement::m_listTextures[(**iterator).getSpriteID()]}));
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
        iterator->second->setSize(iterator->first->getSize().first * viewRatio.first, iterator->first->getSize().second * viewRatio.second);
        iterator->second->setPosition(iterator->first->getPosition().first * viewRatio.first, iterator->first->getPosition().second * viewRatio.second);
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
