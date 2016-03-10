#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "movableelement.h"
#include "graphicelement.h"
#include "game.h"
#include "window.h"

class GameView:Window
{
private:
    Game *m_gameModel;
    std::map <MovableElement*, GraphicElement*> m_elementToGraphicElement;
    RenderWindow *m_renderWindow;
public:
    void draw() const;
    void treatEvent();
    void setModel(const Game *model);
};

#endif // GAMEVIEW_H
