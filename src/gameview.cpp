/*Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#include "gameview.h"
#include <iostream>

bool GameView::treatEvent()
{
    bool quitter = false;
    std::vector<std::pair<bool, GameCharacter*> >::iterator player1 = m_model->getCharacters().begin();
    while (player1 != m_model->getCharacters().end() && player1->second->getId() != character_id::PLAYER1)
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
            case sf::Keyboard::Escape:
                m_model->setPause(!m_model->isPause());
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
        case sf::Event::MouseButtonReleased:
            switch (m_window->getEvent()->mouseButton.button)
            {
            case sf::Mouse::Left:
            {
                unsigned int nbButtons = m_model->getButtons().size();
                for (unsigned int i = 0; i<nbButtons; i++)
                {
                    if (m_model->getButtons()[i].second->isHover(m_model->getCursorPosition().first, m_model->getCursorPosition().second))
                    {
                        m_model->getButtons()[i].second->onClick();
                        break;
                    }
                }
                break;
            }
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
