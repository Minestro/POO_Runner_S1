#ifndef MENU_H
#define MENU_H

#include "model.h"
#include "elementslist.h"

enum menuPage {ESCAPE_MENU, PRE_MENU, HOME, GAME_MODE_SELECTION, SHOP, SETTINGS, HIGHSCORE, PAUSE, RULES, BONUSLIST, INTRO_GAME, SELECT_SAVEFILE};

class Menu: public Model
{
private:
    int m_activePage;
    bool m_exitApp;
    static std::vector<ElementsList> menuModels;
public:
    Menu(float width, float height, int activePage, App *app);
    virtual ~Menu() = default;
    void setPage(unsigned int page);
    void refresh();
    int getActivePage() const;
    std::string getClassName() const;
    bool getExitApp() const;
    void exitApp();
    static void refreshPageContent(Model *model, int page);
    static void loadModels(App *app);
};

#endif // MENU_H
