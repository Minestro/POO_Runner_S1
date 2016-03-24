#include "gameview.h"

GameView::GameView()
{

}

void GameView::draw() const
{
    m_window->clear();
    m_window->display();
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
