#ifndef MENU_H
#define MENU_H

#include "model.h"

enum menuPage {ESCAPE_MENU, PRE_MENU, HOME, GAME_MODE_SELECTION, SHOP, SETTINGS, HIGHSCORE, PAUSE};

class Menu: public Model
{
private:
    int m_activePage;
    int m_backgroundMovePeriod;
public:
    Menu() = default;
    Menu(float width, float height, int activePage);
    virtual ~Menu() = default;
    virtual std::pair<float, float> getCharacterSpeed(const GameCharacter *gc) const;
    void changePage(int page);
    void refresh();
    int getActivePage() const;
};

#endif // MENU_H
