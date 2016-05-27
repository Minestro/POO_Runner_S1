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

#ifndef BUTTON_H
#define BUTTON_H

#include "element.h"
#include "player.h"
#include <vector>
#include <string>

enum button_type {TEXT_BUTTON, ARROW_BUTTON, RADIO_BUTTON, SAVE_BUTTON};
enum button_action {CHANGE_PAGE, EXIT_APP, SET_FULL_SCREEN, RESUME_GAME, RESET_GAME, SET_SELECTED, ERASE_SAVE, LOAD_SAVE, REFRESH_VIEW, SET_PLAYER_NAME, SAVE_GAME_BUTTON, SET_MUSIC, SET_SOUNDS, BUY_UPGRADE, SET_LANG, REFRESH_LANGS};

class Model;

class Button: public Element
{
private:
    std::string m_text;
    int m_type;
    bool m_isClickable;
    bool m_isOn;                    //Pour les boutons du type radio
    bool m_isSelected;
    int m_destinationPage;
    Model *m_model;
    std::vector<int> m_actions;     //Une liste d'actions à executer lors du clique sur le bouton
public:
    Button(float x, float y, float width, float height, float rotation, std::string text, int destinationPage, Model *m, int type = button_type::TEXT_BUTTON, bool isClickable = 1);
    virtual ~Button() = default;
    bool isHover(int x, int y) const;
    void onClick();
    std::string getText() const;
    int getType() const;
    int getDestinationPage() const;
    bool isClickable() const;
    bool isOn() const;
    bool isSelected() const;
    void setSelected(bool selected);
    void setIsOn(bool on);
    void setText(std::string text);
    std::string getClassName() const;
    void addAction(int action);

    Button *getTheSelectedButton();
    const Button *getTheSelectedButton() const;
};

#endif // BUTTON_H
