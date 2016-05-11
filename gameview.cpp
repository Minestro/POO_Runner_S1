#include "gameview.h"
#include <iostream>

bool GameView::treatEvent()
{
    bool quitter = false;
    std::vector<std::pair<bool, GameCharacter*> >::iterator player1 = m_model->getCharacters().begin();
    while (player1 != m_model->getCharacters().end() && player1->second->getId() != 0)
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
            if (m_model->getGameState() == game_state::INTRO)
            {
                m_model->setGameState(game_state::RUNNING);
            }
            switch (m_window->getEvent()->key.code)
            {
            case sf::Keyboard::Right :
                if (player1 != m_model->getCharacters().end())
                {
                    player1->second->rightMove(1);
                }
                break;
            case sf::Keyboard::Left :
                if (player1 != m_model->getCharacters().end())
                {
                    player1->second->leftMove(1);
                }
                break;
            case sf::Keyboard::Up :
                if (player1 != m_model->getCharacters().end())
                {
                    player1->second->ascend(1);
                }
            break;
            case sf::Keyboard::A :
                m_model->getCharacters()[0].second->addScore(100);
                break;
            default:
                break;
            }
            break;
        case sf::Event::KeyReleased :
            switch (m_window->getEvent()->key.code) {
            case sf::Keyboard::Left:
                if (player1 != m_model->getCharacters().end())
                {
                    player1->second->leftMove(0);
                }
                break;
            case sf::Keyboard::Right:
                if (player1 != m_model->getCharacters().end())
                {
                    player1->second->rightMove(0);
                }
                break;
            case sf::Keyboard::Up:
                if (player1 != m_model->getCharacters().end())
                {
                    player1->second->ascend(0);
                }
            default:
                break;
            }
            break;
        case sf::Event::MouseMoved:
            m_model->setCursorPosition(m_window->mapPixelToCoords(sf::Vector2i{sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y}).x, m_window->mapPixelToCoords(sf::Vector2i{sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y}).y);
            break;
        default:
            break;
        }
    }
    return quitter;
}
