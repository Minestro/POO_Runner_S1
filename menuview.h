#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <SFML/Graphics.hpp>
#include "menu.h"
#include "window.h"
#include "spriteelement.h"
#include "circleshapeelement.h"
#include "rectangleshapeelement.h"
#include "lifebar.h"
#include "textelement.h"
#include "gamecharactergraphic.h"
#include "scoregraphic.h"
#include "buttongraphic.h"

class MenuView
{
private:
    Menu *m_menuModel;
    std::map <const Element*, std::list<GraphicElement*> > m_elementToGraphicElement;
    std::vector <const GraphicElement*> m_drawableElementsList;
    Window *m_window;

    void insertGraphicElementIntoList(GraphicElement *ge);
    void fillGraphicElementsList();
public:
    MenuView();
    void draw();
    bool treatEvent();
    void synchronise();
    void setModel(Menu *model);
    void setWindow(Window *window);
};

#endif // MENUVIEW_H
