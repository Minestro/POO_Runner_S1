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
    GraphicElement ge{0, 800, 100, 0, 0, GraphicElement::m_listTextures[0]};
    m_window->draw(ge);
    m_window->display();
}

void GameView::synchronise()
{
    if (m_gameModel->getNewElements().size() > 0)
    {
        std::vector<const Element*>::const_iterator iterator = m_gameModel->getNewElements().begin();
        while (iterator != m_gameModel->getNewElements().end())
        {
            m_elementToGraphicElement.insert(std::make_pair(*iterator, new GraphicElement{0, (**iterator).getSize().first, (**iterator).getSize().second, (**iterator).getPosition().first, (**iterator).getPosition().second, GraphicElement::m_listTextures[(**iterator).getSpriteID()]}));
            ++iterator;
        }
        m_gameModel->getDeletedElements().clear();
    }
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
    std::map <const Element*, GraphicElement*>::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        iterator->second->setSize(iterator->first->getSize().first, iterator->first->getSize().second);
        iterator->second->setPosition(iterator->first->getPosition().first, iterator->first->getPosition().second);
        ++iterator;
    }
}

void GameView::fillGraphicElementsList()
{
    m_graphicElementsList.clear();
    std::map <const Element*, GraphicElement*>::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        m_graphicElementsList.insert(m_graphicElementsList.begin(), iterator->second);
        ++iterator;
    }
}
