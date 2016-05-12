#include <iostream>
#include "window.h"
#include "game.h"
#include "gameview.h"
#include "textelement.h"
#include "menu.h"
#include "menuview.h"
#include "appsettings.h"

int main()
{
    std::chrono::time_point<std::chrono::system_clock> loopTime;
    loopTime = std::chrono::system_clock::now();
    int drawPeriod = (1.0f / FPS)*1000;
    bool quitter = false;

    Window superfenetre{"Runner", sf::Style::Default, GAME_SIZE_W, GAME_SIZE_H};
    AppSettings setting{};
    GraphicElement::loadTextures();
    TextElement::loadFonts();
    Game *gameModel = new Game{GAME_SIZE_W, GAME_SIZE_H, STARTSPEEDPERIODGAME};
    GameView *gameView = new GameView{};
    Menu *menuModel = new Menu{GAME_SIZE_W, GAME_SIZE_H, menuPage::PRE_MENU};
    MenuView *menuView = new MenuView{};
    gameView->setModel(gameModel);
    gameView->setWindow(&superfenetre);
    menuView->setModel(menuModel);
    menuView->setWindow(&superfenetre);
    gameModel->setAppSettings(&setting);
    menuModel->setAppSettings(&setting);
    while (!quitter)
    {
        sf::sleep(sf::milliseconds(1));
        if (menuModel->getActivePage() == menuPage::ESCAPE_MENU)
        {
            gameModel->nextStep();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-loopTime).count() >= drawPeriod)
            {
                gameView->synchronise();
                gameView->draw();
                loopTime = std::chrono::system_clock::now();
            }
            quitter = gameView->treatEvent();
        } else {
            menuModel->refresh();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-loopTime).count() >= drawPeriod)
            {
                menuView->synchronise();
                menuView->draw();
                loopTime = std::chrono::system_clock::now();
            }
            quitter = menuView->treatEvent();
        }
        superfenetre.refreshSettings(setting);
    }
    GraphicElement::clearTextures();
    TextElement::clearFonts();
    delete gameModel;
    delete menuModel;
    delete gameView;
    delete menuView;
    superfenetre.close();
    return EXIT_SUCCESS;
}
