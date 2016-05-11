#include "menuview.h"


bool MenuView::treatEvent()
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
        case sf::Event::MouseMoved:
            m_model->setCursorPosition(m_window->mapPixelToCoords(sf::Vector2i{sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y}).x, m_window->mapPixelToCoords(sf::Vector2i{sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y}).y);
            break;
        case sf::Event::MouseButtonPressed:
            switch (m_window->getEvent()->mouseButton.button)
            {
            case sf::Mouse::Left:
                for (unsigned int i = 0; i<m_model->getButtons().size(); i++)
                {
                    if (m_model->getButtons()[i].second->isHover(m_model->getCursorPosition().first, m_model->getCursorPosition().second))
                    {
                        m_model->getButtons()[i].second->onClick();
                    }
                }
                break;
            default:
                break;
            }
            break;
        case sf::Event::KeyPressed:
            if (m_model->getActivePage() == menuPage::PRE_MENU)
            {
                m_model->setPage(menuPage::HOME);
            }
            break;
        default:
            break;
        }
    }
    return quitter;
}
