#ifndef MENU_H
#define MENU_H

#include "page.h"
#include "model.h"

class Menu: public Model
{
private:
    std::pair<float, float> m_size;
    std::vector <Page*> m_pageList;
    int m_activePage;
public:
    Menu();
    virtual std::pair<float, float> getCharacterSpeed(const GameCharacter *gc) const;
};

#endif // MENU_H
