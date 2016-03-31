#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <set>
#include "animableelement.h"
#include "simplegraphicelement.h"
#include "game.h"
#include "window.h"

struct compGraphicElement
{
    bool operator()(const GraphicElement *g1, const GraphicElement *g2) const;
};

class GameView
{
private:
    Game *m_gameModel;
    std::map <const Element*, GraphicElement*> m_elementToGraphicElement;
    std::set <const GraphicElement*, compGraphicElement> m_graphicElementsList;
    Window *m_window;
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
