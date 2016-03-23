#ifndef MENU_H
#define MENU_H

#include "page.h"

#define accueil 0
#define options 1

class Menu
{
private:
    std::vector <Page*> m_pageList;
    int m_activePage;
public:
    Menu();
};

#endif // MENU_H
