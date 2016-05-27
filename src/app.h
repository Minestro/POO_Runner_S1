#ifndef APP_H
#define APP_H

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

#include <chrono>
#include "window.h"
#include "game.h"
#include "menu.h"
#include "appsettings.h"
#include "menuview.h"
#include "gameview.h"
#include "sound.h"

class App
{
private:
    Window m_window;
    AppSettings m_settings;
    Game m_gameModel;
    GameView m_gameView;
    Menu m_menuModel;
    MenuView m_menuView;
    Sound m_sound;
    std::chrono::time_point<std::chrono::system_clock> m_drawTime;
    unsigned int m_drawPeriod;
    bool m_running;

public:
    App();
    ~App();
    Window &getWindow();
    const Window &getWindow() const;
    AppSettings &getSettings();
    const AppSettings &getSettings() const;
    Game &getGameModel();
    const Game &getGameModel() const;
    GameView &getGameView();
    const GameView &getGameView() const;
    Menu &getMenuModel();
    const Menu &getMenuModel() const;
    MenuView &getMenuView();
    const MenuView &getMenuView() const;
    Sound &getSound();
    const Sound &getSound() const;
    void run();
    void stop();
};

#endif // APP_H
