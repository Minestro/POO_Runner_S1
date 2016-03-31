#ifndef MENU_H
#define MENU_H

#include "page.h"
#include "const.h"

class Menu
{
private:
    std::pair<float, float> m_size;
    std::vector <Page*> m_pageList;
    int m_activePage;
public:
    Menu();
};

#endif // MENU_H
