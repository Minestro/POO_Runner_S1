#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <SFML/Graphics.hpp>
#include <set>
#include <typeinfo>
#include "game.h"
#include "window.h"
#include "spriteelement.h"
#include "circleshapeelement.h"
#include "rectangleshapeelement.h"
#include "lifebar.h"
#include "textelement.h"
#include "gamecharactergraphic.h"


class GameView
{
private:
    Game *m_gameModel;
    std::map <const Element*, std::list<GraphicElement*> > m_elementToGraphicElement;
    std::vector <const GraphicElement*> m_drawableElementsList;
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
