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

#include "button.h"
#include "model.h"
#include "app.h"

using namespace tinyxml2;
using namespace runner;

Button::Button(float x, float y, float width, float height, float rotation, std::string text, int destinationPage, Model *m, int type, bool isClickable): Element::Element{x, y, width, height, rotation}, m_text{text}, m_type{type}, m_isClickable{isClickable}, m_isOn{0}, m_isSelected{0}, m_destinationPage{destinationPage}, m_model{m}, m_actions{}
{

}

std::string Button::getClassName() const
{
    return "Button";
}

std::string Button::getText() const
{
    std::string finalText = m_text;
    if (m_type == button_type::SAVE_BUTTON) //Pour les boutons de selection du profil qui affichent une courte description du joueur
    {
        try
        {
            bool isActive = Player::isActive(m_id - menu_specific_elements::SELECT_SAVE_1);
            if (!isActive)
            {
                finalText = Text::getMessage(m_model->getApp()->getSettings().m_lang, "EMPTY");
            } else {
                Player pla{m_id - menu_specific_elements::SELECT_SAVE_1};
                pla.loadSaveFromFile();
                finalText =  "    " + pla.getName() + " \n \n" + runner::Text::getMessage(m_model->getApp()->getSettings().m_lang, "BSCORE") + " : " + std::to_string(pla.getBestScore()) + " \n" + runner::Text::getMessage(m_model->getApp()->getSettings().m_lang, "MONEY") + " : " + std::to_string(pla.getMoney());
            }
        }
        catch (tinyxml2::XMLError er)
        {
            std::cout << "Error when trying to load profile. Code : " << std::to_string(er) << std::endl;
        }
    }
    return finalText;
}

int Button::getType() const
{
    return m_type;
}

bool Button::isClickable() const
{
    bool isClickable = m_isClickable;
    switch (m_id)
    {
    case menu_specific_elements::ERASE_SAVE_BUTTON:
    {
        const Button *selected = getTheSelectedButton();
        if (selected != nullptr)
        {
            if (selected->getId() >= menu_specific_elements::SELECT_SAVE_1 && selected->getId() <= menu_specific_elements::SELECT_SAVE_5)
            {
                try
                {
                    isClickable = Player::isActive(selected->getId() - menu_specific_elements::SELECT_SAVE_1);
                }
                catch (XMLError e)
                {
                    std::cout << "Error when trying to write profile file. Code : " << std::to_string(e) << std::endl;
                }
            }
        }
        break;
    }
    case menu_specific_elements::UPGRADE_BUTTON1:
        if (m_model->getApp()->getGameModel().getPlayer()->getMoney() >= UPGRADE_COST && m_model->getApp()->getGameModel().getPlayer()->getTimePower(m_id - menu_specific_elements::UPGRADE_BUTTON1) < MAX_UPGRADE_SEC*1000)
        {
            isClickable = true;
        } else {
            isClickable = false;
        }
        break;
    case menu_specific_elements::UPGRADE_BUTTON2:
        if (m_model->getApp()->getGameModel().getPlayer()->getMoney() >= UPGRADE_COST && m_model->getApp()->getGameModel().getPlayer()->getTimePower(m_id - menu_specific_elements::UPGRADE_BUTTON1) < MAX_UPGRADE_SEC*1000)
        {
            isClickable = true;
        } else {
            isClickable = false;
        }
        break;
    case menu_specific_elements::UPGRADE_BUTTON3:
        if (m_model->getApp()->getGameModel().getPlayer()->getMoney() >= UPGRADE_COST && m_model->getApp()->getGameModel().getPlayer()->getTimePower(m_id - menu_specific_elements::UPGRADE_BUTTON1) < MAX_UPGRADE_SEC*1000)
        {
            isClickable = true;
        } else {
            isClickable = false;
        }
        break;
    default:
        break;
    }

    return isClickable;
}

bool Button::isOn() const
{
    bool isOn = m_isOn;
    switch (m_id)
    {
    case menu_specific_elements::FULL_SCREEN_BUTTON:
        isOn = m_model->getApp()->getSettings().m_isFullScreen;
        break;
    case menu_specific_elements::MUSIC_ACTIVE_BUTTON:
        isOn = m_model->getApp()->getSettings().m_musicVolume == 100;
        break;
    case menu_specific_elements::SOUNDS_ACTIVE_BUTTON:
        isOn = m_model->getApp()->getSettings().m_effectVolume == 100;
        break;
    default:
        break;
    }
    if (m_id >= menu_specific_elements::LANG_BUTTON)
    {
        isOn = m_model->getApp()->getSettings().m_lang == m_id - menu_specific_elements::LANG_BUTTON;
    }
    return isOn;
}

void Button::setIsOn(bool on)
{
    m_isOn = on;
}

bool Button::isSelected() const
{
    return m_isSelected;
}

void Button::setSelected(bool selected)
{
    for (std::pair<bool, Button*> b: m_model->getButtons())
    {
        b.second->m_isSelected = 0;
    }
    m_isSelected = selected;
}

void Button::setText(std::string text)
{
    m_text = text;
}

void Button::addAction(int action)
{
    m_actions.push_back(action);
}

//------------------------------------------------------------------------------
// Input:   x : coordonnées de la souris en x
//          y : coordonnées de la souris en y
// Output:  Rien
// Return:  Booléen
// Purpose: Fonction qui renvoie si le bouton est survolé par la souris
//------------------------------------------------------------------------------
bool Button::isHover(int x, int y) const
{
    return (x < m_position.first + m_size.first && x > m_position.first && y < m_position.second + m_size.second && y > m_position.second);
}

void Button::onClick()
{
    if (isClickable())
    {
        for (unsigned int i=0; i<m_actions.size(); i++)
        {
            switch (m_actions[i])
            {
            case button_action::CHANGE_PAGE:
                m_model->getApp()->getMenuModel().setPage(m_destinationPage);
                break;
            case button_action::EXIT_APP:
                m_model->getApp()->getMenuModel().exitApp();
                break;
            case button_action::SET_FULL_SCREEN:
                m_model->getApp()->getSettings().m_isFullScreen = !m_model->getApp()->getSettings().m_isFullScreen;
                break;
            case button_action::SET_MUSIC:
                if (m_model->getApp()->getSettings().m_musicVolume == 100)
                {
                    m_model->getApp()->getSettings().m_musicVolume = 0;
                } else {
                    m_model->getApp()->getSettings().m_musicVolume = 100;
                }
                m_model->getApp()->getSound().stopAll();
                m_model->getApp()->getSound().playMusic();
                break;
            case button_action::SET_SOUNDS:
                if (m_model->getApp()->getSettings().m_effectVolume == 100)
                {
                    m_model->getApp()->getSettings().m_effectVolume = 0;
                } else {
                    m_model->getApp()->getSettings().m_effectVolume = 100;
                }
                break;
            case button_action::BUY_UPGRADE:
                if (m_id >= menu_specific_elements::UPGRADE_BUTTON1 && m_id <= menu_specific_elements::UPGRADE_BUTTON3)
                {
                    m_model->getApp()->getGameModel().getPlayer()->buy(m_id - menu_specific_elements::UPGRADE_BUTTON1);
                    try
                    {
                        m_model->getApp()->getGameModel().getPlayer()->saveProfile();
                    }
                    catch (XMLError e)
                    {
                        std::cout << "Error when trying to save profile. Code : " << std::to_string(e) << std::endl;
                    }
                }
                break;
            case button_action::RESUME_GAME:
                m_model->getApp()->getGameModel().setPause(0);
                break;
            case button_action::RESET_GAME:
                m_model->getApp()->getGameModel().resetGame();
                break;
            case button_action::REFRESH_VIEW:
                Menu::refreshPageContent(m_model, m_model->getApp()->getMenuModel().getActivePage());
                break;
            case button_action::SET_LANG:
                if (m_id >= menu_specific_elements::LANG_BUTTON && m_id <= menu_specific_elements::LANG_BUTTON + Text::getLangsList().size())
                {
                    m_model->getApp()->getSettings().m_lang = m_id - menu_specific_elements::LANG_BUTTON;
                }
                break;
            case button_action::SET_SELECTED:
            {
                setSelected(1);
                if (m_model->getApp()->getMenuModel().getActivePage() == menuPage::SELECT_SAVEFILE && m_type == button_type::SAVE_BUTTON)
                {
                    for (std::pair <bool, Button*> &b: m_model->getApp()->getMenuModel().getButtons())
                    {
                        if (b.second->getId() == menu_specific_elements::LOAD_SAVE_BUTTON)
                        {
                            if (Player::isActive(m_id - menu_specific_elements::SELECT_SAVE_1) == true)
                            {
                                b.second->setText(Text::getMessage(m_model->getApp()->getSettings().m_lang, "LOAD"));
                            } else {
                                b.second->setText(Text::getMessage(m_model->getApp()->getSettings().m_lang, "NEW"));
                            }
                        }
                    }
                }
                break;
            }
            case button_action::LOAD_SAVE:
            {
                try
                {
                    Button *selected = getTheSelectedButton();
                    m_model->getApp()->getMenuModel().setPage(menuPage::HOME);
                    if (selected != nullptr)
                    {
                        if (selected->getId() >= menu_specific_elements::SELECT_SAVE_1 && selected->getId() <= menu_specific_elements::SELECT_SAVE_5)
                        {
                            m_model->getApp()->getGameModel().setPlayer(new Player{selected->getId() - menu_specific_elements::SELECT_SAVE_1});
                            if (!Player::isActive(selected->getId() - menu_specific_elements::SELECT_SAVE_1))
                            {
                                Player::eraseProfil(selected->getId() - menu_specific_elements::SELECT_SAVE_1);
                                m_model->getApp()->getMenuModel().setPage(menuPage::CHARACCTER_SET_NAME);
                            }
                        } else {
                            m_model->getApp()->getGameModel().setPlayer(new Player{});
                        }
                    } else {
                        m_model->getApp()->getGameModel().setPlayer(new Player{});
                    }
                }
                catch (XMLError e)
                {
                    std::cout << "Error when trying to load profile. Code : " << std::to_string(e) << std::endl;
                }

                break;
            }
            case button_action::ERASE_SAVE:
            {
                Button *selected = getTheSelectedButton();
                if (selected != nullptr)
                {
                    if (selected->getId() >= menu_specific_elements::SELECT_SAVE_1 && selected->getId() <= menu_specific_elements::SELECT_SAVE_5)
                    {
                        try
                        {
                            Player::eraseProfil(selected->getId() - menu_specific_elements::SELECT_SAVE_1);
                        }
                        catch (XMLError e)
                        {
                            std::cout << "Error when trying to load profile. Code : " << std::to_string(e) << std::endl;
                        }
                    }
                }
                break;
            }
            case button_action::SET_PLAYER_NAME:
            {
                std::vector<std::pair<bool, Text*> >::iterator textBox = m_model->getTexts().begin();
                while (textBox != m_model->getTexts().end() && textBox->second->getId() != menu_specific_elements::INPUT_TEXT)
                {
                    ++textBox;
                }
                if (textBox != m_model->getTexts().end())
                {
                    m_model->getApp()->getGameModel().getPlayer()->setNickName(textBox->second->getText());
                    try
                    {
                        m_model->getApp()->getGameModel().getPlayer()->saveProfile();
                        m_model->getApp()->getMenuModel().setPage(menuPage::HOME);
                    }
                    catch (XMLError e)
                    {
                        std::cout << "Error when trying to save profile. Code : " << std::to_string(e) << std::endl;
                    }
                }
                break;
            }
            case button_action::SAVE_GAME_BUTTON:
            {
                GameCharacter *player1 = m_model->getApp()->getGameModel().getCharacterById(character_id::PLAYER1);
                if (player1 != nullptr)
                {
                    m_model->getApp()->getGameModel().getPlayer()->addMoney(player1->getScore()/1000);
                    if (m_model->getApp()->getGameModel().getPlayer()->getBestScore() < player1->getScore())
                    {
                        m_model->getApp()->getGameModel().getPlayer()->setBestScore(player1->getScore());
                    }
                    try
                    {
                        m_model->getApp()->getGameModel().getPlayer()->saveProfile();
                    }
                    catch (XMLError e)
                    {
                        std::cout << "Error when trying to save profile. Code : " << std::to_string(e) << std::endl;
                    }
                }
                break;
            }
            case button_action::REFRESH_LANGS:
                Menu::loadModels(m_model->getApp());
            default:
                break;
            }
        }
    }
}

int Button::getDestinationPage() const
{
    return m_destinationPage;
}

Button *Button::getTheSelectedButton()
{
    std::vector<std::pair<bool, Button*> >::iterator button = m_model->getButtons().begin();
    while (button != m_model->getButtons().end() && !button->second->isSelected())
    {
        ++button;
    }
    if (button != m_model->getButtons().end())
    {
        return button->second;
    } else {
        return nullptr;
    }
}

const Button *Button::getTheSelectedButton() const
{
    std::vector<std::pair<bool, Button*> >::const_iterator button = m_model->getButtons().begin();
    while (button != m_model->getButtons().end() && !button->second->isSelected())
    {
        ++button;
    }
    if (button != m_model->getButtons().end())
    {
        return button->second;
    } else {
        return nullptr;
    }
}
