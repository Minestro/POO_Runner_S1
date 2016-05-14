#ifndef APP_H
#define APP_H

#include <chrono>
#include "window.h"
#include "game.h"
#include "menu.h"
#include "appsettings.h"
#include "menuview.h"
#include "gameview.h"

class Element;

class App
{
private:
    Window m_window;
    AppSettings m_settings;
    Game m_gameModel;
    GameView m_gameView;
    Menu m_menuModel;
    MenuView m_menuView;
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
    void run();
    void stop();
};

#endif // APP_H
