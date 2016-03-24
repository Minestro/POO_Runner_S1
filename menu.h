#ifndef MENU_H
#define MENU_H

#include "page.h"

const int MENU_SIZE_W = 800;
const int MENU_SIZE_H = 600;

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
