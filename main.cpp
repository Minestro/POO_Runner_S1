#include <iostream>
#include "window.h"
#include "game.h"
#include "gameview.h"
#include "graphicelement.h"
#include "menu.h"
#include "menuview.h"

void wait (int time)
{
    std::chrono::time_point<std::chrono::system_clock> begin;
    begin = std::chrono::system_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-begin).count() < time)
    {

    }
}

int main()
{
    std::chrono::time_point<std::chrono::system_clock> loopTime;
    loopTime = std::chrono::system_clock::now();
    int drawPeriod = (1.0f / FPS)*1000000;
    bool quitter = false;
    Window superfenetre{"Runner", sf::Style::Default, GAME_SIZE_W, GAME_SIZE_H};
    GraphicElement::loadTextures();
    Game gameModel{};
    GameView gameView{};
    Menu menuModel;
    MenuView menuView;
    gameView.setModel(&gameModel);
    gameView.setWindow(&superfenetre);
    menuView.setModel(&menuModel);
    menuView.setWindow(&superfenetre);
    while (!quitter)
    {
        wait(1);
        gameModel.nextStep();
        gameView.synchronise();
        if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-loopTime).count() > drawPeriod)
        {
            gameView.draw();
            loopTime = std::chrono::system_clock::now();
        }
        quitter = gameView.treatEvent();
    }
    return 0;
}
