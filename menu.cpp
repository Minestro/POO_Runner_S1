#include "menu.h"
#include <iostream>

using namespace tinyxml2;

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
    for (unsigned int i = 200; i<222; i++)
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
        for (unsigned int i = button_id::SELECT_SAVE_1; i<button_id::SELECT_SAVE_5+1; i++)
        {
            Button *b = new Button{(float)20 + (j*250) , 160, 240, 200, 0, "", menuPage::SELECT_SAVEFILE, model->getApp(), button_type::SAVE_BUTTON, 1};
            b->setId(i);
            b->addAction(button_action::SET_SELECTED);
            model->getButtons().push_back(std::make_pair(1, b));
            j++;
        }
        Button *b2 = new Button{MODEL_SIZE_W/2 - 300 , 600, 200, 50, 0, "Charger", menuPage::SELECT_SAVEFILE, model->getApp(), button_type::TEXT_BUTTON, 1};
        b2->setId(button_id::LOAD_SAVE_BUTTON);
        b2->addAction(button_action::LOAD_SAVE);
        model->getButtons().push_back(std::make_pair(1, b2));
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
        op.loadFromFile(modelsFile, app);
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
