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

#include "menuview.h"

bool MenuView::treatEvent()
{
    bool quitter = m_model->getExitApp();
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
        case sf::Event::KeyPressed:
            if (m_model->getActivePage() == menuPage::PRE_MENU)
            {
                m_model->setPage(menuPage::SELECT_SAVEFILE);
            }
            break;
        case sf::Event::TextEntered:
        {
           for (std::pair<bool, runner::Text*> &textBox : m_model->getTexts())
           {
               if (textBox.second->getId() == menu_specific_elements::INPUT_TEXT)
               {
                   if (m_window->getEvent()->text.unicode == '\b' && textBox.second->getText().size()!=0)
                   {
                       textBox.second->getText().pop_back();
                   }
                   else if (m_window->getEvent()->text.unicode < 128 && textBox.second->getText().size() < MAX_NICKNAME_LENGHT)
                   {
                       textBox.second->getText().push_back((char)m_window->getEvent()->text.unicode);
                   }
               }
           }
            break;
        }
        default:
            break;
        }
    }
    return quitter;
}
