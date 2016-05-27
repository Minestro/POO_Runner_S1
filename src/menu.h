/*Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#ifndef MENU_H
#define MENU_H

#include "model.h"
#include "elementslist.h"

enum menuPage {ESCAPE_MENU, PRE_MENU, HOME, GAME_MODE_SELECTION, SHOP, SETTINGS, HIGHSCORE, PAUSE, RULES, BONUSLIST, INTRO_GAME, SELECT_SAVEFILE, CHARACCTER_SET_NAME, GAME_ENDED}; //Id des pages
enum menu_specific_elements {FULL_SCREEN_BUTTON = 200, MUSIC_ACTIVE_BUTTON, SOUNDS_ACTIVE_BUTTON, LOAD_SAVE_BUTTON, ERASE_SAVE_BUTTON, INPUT_TEXT, UPGRADE_BUTTON1, UPGRADE_BUTTON2, UPGRADE_BUTTON3, SELECT_SAVE_1, SELECT_SAVE_2, SELECT_SAVE_3, SELECT_SAVE_4, SELECT_SAVE_5, LANG_BUTTON = 270}; //On va attribuer des id spécifiques à certains éléments du menu qui on une action particulière. Les éléments du menu ont un id allant de 200 à 300 pour les reconnaître lors du changement de page, cela évite que les autres éléments du modèle comme le character, les obstacles soient supprimés

class Menu: public Model
{
private:
    int m_activePage;
    bool m_exitApp;     //Indique à l'app de se quitter
    static std::vector<ElementsList> menuModels;
public:
    Menu(float width, float height, int activePage, App *app);
    virtual ~Menu() = default;
    void setPage(unsigned int page);        //Ajoute les éléments d'une page au modèle
    void refresh();
    int getActivePage() const;
    std::string getClassName() const;
    bool getExitApp() const;
    void exitApp();
    static void refreshPageContent(Model *model, int page);
    static void loadModels(App *app);
};

#endif // MENU_H
