#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <set>
#include <typeinfo>
#include "animableelement.h"
#include "game.h"
#include "window.h"


class GameView
{
private:
    Game *m_gameModel;
    std::map <const Element*, GraphicElement*> m_elementToGraphicElement;
    std::vector <const GraphicElement*> m_graphicElementsList;
    Window *m_window;
    void insertGraphicElementIntoList(GraphicElement *ge);
public:
    GameView();
    void draw();
    bool treatEvent();
    void fillGraphicElementsList();
    void synchronise();
    void setModel(Game *model);
    void setWindow(Window *window);
};

#endif // GAMEVIEW_H
