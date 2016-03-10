#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <SFML/Graphics.hpp>
#include "menu.h"
#include "window.h"

class MenuView:Window
{
private:
    Menu *m_menuModel;
    RenderWindow *m_renderWindow;
public:
    MenuView();
    void setModel(const Menu *model);
    void treatEvent();
    void draw() const;
};

#endif // MENUVIEW_H
