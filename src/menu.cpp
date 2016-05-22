#include "menu.h"
#include "app.h"
#include <iostream>

using namespace tinyxml2;
using namespace runner;

std::vector<ElementsList> Menu::menuModels;

Menu::Menu(float width, float height, int activePage, App *app): Model::Model{width, height, app}, m_activePage{activePage}, m_exitApp{0}
{

}

void Menu::setPage(unsigned int page)
{
    m_activePage = page;
    refreshPageContent(this, m_activePage);
}

void Menu::refreshPageContent(Model *model, int page)
{
    for (unsigned int i = 200; i<232; i++)
    {
        model->deleteElement(i);
    }
    std::vector<ElementsList>::iterator preMenu = Menu::menuModels.begin();
    while (preMenu != Menu::menuModels.end() && preMenu->getId() != (unsigned int)page)
    {
        ++preMenu;
    }
    if (preMenu != Menu::menuModels.end())
    {
        preMenu->addElementsToModel(model);
    }

   if (page == menuPage::SELECT_SAVEFILE)
   {
       unsigned int j=0;
        for (unsigned int i = menu_specific_elements::SELECT_SAVE_1; i<menu_specific_elements::SELECT_SAVE_5+1; i++)
        {
            Button *b = new Button{(float)20 + (j*250) , 160, 240, 200, 0, "", menuPage::SELECT_SAVEFILE, model, button_type::SAVE_BUTTON, 1};
            b->setId(i);
            b->addAction(button_action::SET_SELECTED);
            model->getButtons().push_back(std::make_pair(1, b));
            j++;
        }
        Button *b2 = new Button{MODEL_SIZE_W/2 , 600, 200, 50, 0, "Charger", menuPage::HOME, model, button_type::TEXT_BUTTON, 1};
        b2->setId(menu_specific_elements::LOAD_SAVE_BUTTON);
        b2->addAction(button_action::LOAD_SAVE);

        Button *b3 = new Button{MODEL_SIZE_W/2 - 300, 600, 200, 50, 0, "Ecraser", menuPage::SELECT_SAVEFILE, model, button_type::TEXT_BUTTON, 1};
        b3->setId(menu_specific_elements::ERASE_SAVE_BUTTON);
        b3->addAction(button_action::ERASE_SAVE);
        b3->addAction(button_action::REFRESH_VIEW_BUTTONS);

        model->getButtons().push_back(std::make_pair(1, b2));
        model->getButtons().push_back(std::make_pair(1, b3));
   } else if (page == menuPage::CHARACCTER_SET_NAME)
   {
        Text *t = new runner::Text{440, 200, 400, 50, 0, "", 20, "The_Happy_Giraffe.ttf", ColorRGBA::Black, text_effect::NOTHING, 0, 1, 0};
        t->setId(menu_specific_elements::INPUT_TEXT);
        model->getTexts().push_back(std::make_pair(1, t));
   } else if (page == menuPage::GAME_ENDED)
   {
        model->getApp()->getSound().pauseAll();
        GameCharacter *player1 = model->getApp()->getGameModel().getCharacterById(character_id::PLAYER1);
        if (player1 != nullptr)
        {
            if (model->getApp()->getGameModel().getPlayer()->getBestScore() < player1->getScore())
            {
                Text *t = new Text{0, 130, MODEL_SIZE_W, 50, 0, "Meilleur Score !", 20, "The_Happy_Giraffe.ttf", ColorRGBA::Red, text_effect::FLASH, 500, 1, 0};
                t->setId(214);
                model->getTexts().push_back(std::make_pair(1, t));
            }
            Text *t2 = new Text{100, 200, 0, 0, 0, "Score : " + std::to_string(player1->getScore()), 20, "The_Happy_Giraffe.ttf", ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0};
            t2->setId(215);
            Text *t3 = new Text{100, 300, 0, 0, 0, "Argent : " + std::to_string(model->getApp()->getGameModel().getPlayer()->getMoney()) + " + " + std::to_string(player1->getScore()/1000) + " = " + std::to_string(model->getApp()->getGameModel().getPlayer()->getMoney() + player1->getScore()/1000), 20, "The_Happy_Giraffe.ttf", ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0};
            t3->setId(216);
            model->getTexts().push_back(std::make_pair(1, t2));
            model->getTexts().push_back(std::make_pair(1, t3));
        }
   }
}

void Menu::loadModels(App *app)
{
    int nbPatterns = 0;
    int returnCode;
    XMLDocument modelsFile;
    returnCode = modelsFile.LoadFile(MENU_MODELS_FILE.c_str());
    if (returnCode != XML_SUCCESS)
    {
        throw XMLError (returnCode);
    }
    const XMLNode *pRoot = modelsFile.FirstChild();
    if (pRoot == nullptr)
    {
        throw XMLError (XML_ERROR_FILE_READ_ERROR);
    }
    const XMLElement *nbPatternsNode = pRoot->FirstChildElement("NbPatterns");
    if (nbPatternsNode == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    returnCode = nbPatternsNode->QueryIntText(&nbPatterns);
    if (returnCode != XML_SUCCESS)
    {
        throw XMLError (returnCode);
    }
    for (unsigned int i=menuPage::PRE_MENU; (int)i<menuPage::PRE_MENU + nbPatterns; i++)
    {
        ElementsList op{i};
        op.loadFromFile(modelsFile, &app->getMenuModel());
        Menu::menuModels.push_back(op);
    }
}

void Menu::refresh()
{
    for (unsigned int i=0; i<getImages().size(); i++)
    {
        getImages()[i].second->move();
    }
}

int Menu::getActivePage() const
{
    return m_activePage;
}

bool Menu::getExitApp() const
{
    return m_exitApp;
}

std::string Menu::getClassName() const
{
    return "Menu";
}

void Menu::exitApp()
{
    m_exitApp = 1;
}
