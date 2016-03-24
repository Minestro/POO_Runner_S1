#include "gameview.h"

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

void GameView::draw() const
{
    m_window->clear();
    std::map <Element*, GraphicElement*>::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        m_window->draw(*(iterator->second));
        ++iterator;
    }
    m_window->display();
}

void GameView::synchronise()
{
    std::map <Element*, GraphicElement*>::const_iterator iterator = m_elementToGraphicElement.begin();
    while(iterator != m_elementToGraphicElement.end())
    {
        iterator->second->setSize(iterator->first->getSize().first, iterator->first->getSize().second);
        iterator->second->setPosition(iterator->first->getPosition().first, iterator->first->getPosition().second);
        ++iterator;
    }
}
