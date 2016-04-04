#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <vector>
#include "button.h"

class Page
{
private:
    std::vector <Element*> m_elementsList;
public:
    std::vector<Element*> &getElementsList();
};

#endif // MENUPAGE_H
