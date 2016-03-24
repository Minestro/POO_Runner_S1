#include <iostream>
#include "window.h"
#include "game.h"
#include "gameview.h"
#include "graphicelement.h"
#include "menu.h"
#include "menuview.h"

using namespace std;

int main()
{
    bool quitter = false;
    Window superfenetre{"Runner", sf::Style::Close};
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
        gameView.draw();
        quitter = gameView.treatEvent();
    }
    return 0;
}
