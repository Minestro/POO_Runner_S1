#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "view.hpp"

class MenuView: public View<Menu>
{
public:
    MenuView() = default;
    virtual ~MenuView() = default;
    virtual bool treatEvent();
};

#endif // MENUVIEW_H
