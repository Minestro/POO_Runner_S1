#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include "movableelement.h"
#include "graphicelement.h"
#include "game.h"
#include "window.h"

class GameView
{
private:
    Game *m_gameModel;
    std::map <MovableElement*, GraphicElement*> m_elementToGraphicElement;
    Window *m_window;
public:
    void draw() const;
    void treatEvent();
    void setModel(const Game *model);
};

#endif // GAMEVIEW_H
