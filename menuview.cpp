#include "menuview.h"

MenuView::MenuView()
{

}

void MenuView::setModel(Menu *model)
{
    m_menuModel = model;
}

void MenuView::setWindow(Window *window)
{
    m_window = window;
}
