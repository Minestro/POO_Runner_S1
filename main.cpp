#include <iostream>
#include "window.h"
#include "game.h"
#include "gameview.h"
#include "textelement.h"
#include "menu.h"
#include "menuview.h"

int main()
{
    std::chrono::time_point<std::chrono::system_clock> loopTime;
    loopTime = std::chrono::system_clock::now();
    int drawPeriod = (1.0f / FPS)*1000;
    bool quitter = false;
    Window superfenetre{"Runner", sf::Style::Default, GAME_SIZE_W, GAME_SIZE_H};
    GraphicElement::loadTextures();
    TextElement::loadFonts();
    Game gameModel{GAME_SIZE_W, GAME_SIZE_H, STARTSPEEDPERIODGAME};
    GameView gameView{};
    Menu menuModel{GAME_SIZE_W, GAME_SIZE_H, menuPage::HOME};
    MenuView menuView{};
    gameView.setModel(&gameModel);
    gameView.setWindow(&superfenetre);
    menuView.setModel(&menuModel);
    menuView.setWindow(&superfenetre);
    while (!quitter)
    {
        sf::sleep(sf::milliseconds(1));
        if (menuModel.getActivePage() == menuPage::ESCAPE_MENU)
        {
            gameModel.nextStep();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-loopTime).count() > drawPeriod)
            {
                gameView.synchronise();
                gameView.draw();
                loopTime = std::chrono::system_clock::now();
            }
            quitter = gameView.treatEvent();
        } else {
            menuModel.refresh();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-loopTime).count() > drawPeriod)
            {
                menuView.synchronise();
                menuView.draw();
                loopTime = std::chrono::system_clock::now();
            }
            quitter = menuView.treatEvent();
        }
    }
    GraphicElement::clearTextures();
    TextElement::clearFonts();
    return 0;
}
