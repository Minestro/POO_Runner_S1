#ifndef MENU_H
#define MENU_H

#include "model.h"
#include "elementslist.h"

enum menuPage {ESCAPE_MENU, PRE_MENU, HOME, GAME_MODE_SELECTION, SHOP, SETTINGS, HIGHSCORE, PAUSE, RULES, BONUSLIST};

class Menu: public Model
{
private:
    int m_activePage;
    bool m_exitApp;
    std::vector<ElementsList> m_menuModels;
    int loadModels();
public:
    Menu(float width, float height, int activePage);
    virtual ~Menu() = default;
    virtual std::pair<float, float> getCharacterSpeed(const GameCharacter *gc) const;
    void setPage(unsigned int page);
    void refresh();
    int getActivePage() const;
    bool getExitApp() const;
    void exitApp();
    static void refreshPageContent(Model *model, int page);
};

#endif // MENU_H
