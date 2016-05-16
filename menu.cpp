#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height, int activePage): Model::Model{width, height}, m_activePage{activePage}, m_exitApp{0}
{
    setPage(activePage);
}

std::pair<float, float> Menu::getCharacterSpeed(const GameCharacter *gc) const
{
    return (gc->getPixelSpeed());
}

void Menu::setPage(unsigned int page)
{
    m_activePage = page;
    refreshPageContent(this, m_activePage, menuPage::HOME);
}

void Menu::refreshPageContent(Model *model, int page, int returnPage)
{
    model->clearAll();

    switch (page)
    {
    case menuPage::HOME :
    {
        Button *b1 = new Button{model->getSize().first/2 - 100, 150, 200, 50, 0, "Jouer", menuPage::ESCAPE_MENU, & model->getApp(), button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        Button *b2 = new Button{model->getSize().first/2 - 100, 250, 200, 50, 0, "Regles", menuPage::RULES, & model->getApp(), button_type::TEXT_BUTTON};
        b2->addAction(button_action::CHANGE_PAGE);
        Button *b3 = new Button{model->getSize().first/2 - 100, 350, 200, 50, 0, "Options", menuPage::SETTINGS, & model->getApp(), button_type::TEXT_BUTTON};
        b3->addAction(button_action::CHANGE_PAGE);
        Button *b4 = new Button{model->getSize().first/2 - 100, 450, 200, 50, 0, "Quitter", menuPage::ESCAPE_MENU, & model->getApp(), button_type::TEXT_BUTTON};
        b4->addAction(button_action::EXIT_APP);
        Image *i = new Image{0, 0, model->getSize().first, model->getSize().second, "menuBackground.png", 1, 0, 0};

         model->getButtons().push_back(std::make_pair(1, b1));
         model->getButtons().push_back(std::make_pair(1, b2));
         model->getButtons().push_back(std::make_pair(1, b3));
         model->getButtons().push_back(std::make_pair(1, b4));
         model->getImages().push_back(std::make_pair(1, i));
        break;
    }
    case menuPage::PRE_MENU :
    {
        Image *i1 = new Image{0, 0, model->getSize().first, model->getSize().second, "FOND2.png", 1, 0.5, 1, STARTSPEEDPERIODGAME};
        Image *i2 = new Image{0, 0, model->getSize().first, model->getSize().second, "FOND1.png", 2, 1.0, 1, STARTSPEEDPERIODGAME};
        Text *t = new Text{0, 600, model->getSize().first, 50, 0, "Appuyez sur une touche pour continuer", 20, "score.ttf", ColorRGBA::White,text_effect::BREATH, 20, 1, 0};
        model->getImages().push_back(std::make_pair(1, i1));
        model->getImages().push_back(std::make_pair(1, i2));
        model->getTexts().push_back(std::make_pair(1, t));
        break;
    }
    case menuPage::RULES :
    {
        Image *background = new Image{0, 0, model->getSize().first, model->getSize().second, "FOND.png", 1, 0, 0};
        Image *textbox = new Image{model->getSize().first/2 - 250, 100, 500, 400, "textBox.png", 2, 0, 0};
        Text *rules = new Text{model->getSize().first/2 - 250, 100, 500, 70, 0, "Regles", 30, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 1, 0};
        Text *rules2 = new Text{model->getSize().first/2 - 230, 170, 460, 150, 0, "Pilotez l'avion le plus loin possible en evitant les obstacles et en ramassant un maximum de pieces possible !", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 1, 1};
        Image *leftKey = new Image{model->getSize().first/2 - 230, 250, 40, 40, "leftKey.png", 3, 0, 0};
        Image *rightKey = new Image{model->getSize().first/2 - 230, 310, 40, 40, "rightKey.png", 3, 0, 0};
        Image *upKey = new Image{model->getSize().first/2 - 230, 370, 40, 40, "upKey.png", 3, 0, 0};
        Text *reculer = new Text{model->getSize().first/2 - 170, 250, 0, 0, 0, "Reculer", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0};
        Text *avancer = new Text{model->getSize().first/2 - 170, 310, 0, 0, 0, "Avancer", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0};
        Text *monter = new Text{model->getSize().first/2 - 170, 370, 0, 0, 0, "Monter", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0};
        Button *b1 = new Button{model->getSize().first/2 - 250, 550, 200, 50, 0, "Retour", returnPage, & model->getApp(), button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        Button *b2 = new Button{model->getSize().first/2 + 50 , 550, 200, 50, 0, "Liste des objets", menuPage::BONUSLIST, & model->getApp(), button_type::TEXT_BUTTON};
        b2->addAction(button_action::CHANGE_PAGE);

        model->getImages().push_back(std::make_pair(1, background));
        model->getImages().push_back(std::make_pair(1, textbox));
        model->getTexts().push_back(std::make_pair(1, rules));
        model->getTexts().push_back(std::make_pair(1, rules2));
        model->getImages().push_back(std::make_pair(1, leftKey));
        model->getImages().push_back(std::make_pair(1, rightKey));
        model->getImages().push_back(std::make_pair(1, upKey));
        model->getTexts().push_back(std::make_pair(1, reculer));
        model->getTexts().push_back(std::make_pair(1, avancer));
        model->getTexts().push_back(std::make_pair(1, monter));
        model->getButtons().push_back(std::make_pair(1, b1));
        model->getButtons().push_back(std::make_pair(1, b2));
        break;
     }
    case menuPage::BONUSLIST :
    {
        Image *fond = new Image{0, 0, model->getSize().first, model->getSize().second, "FOND.png", 1, 0, 0};
        Image *textBox = new Image{model->getSize().first/2 - 250, 100, 500, 400, "textBox.png", 2, 0, 0};
        Button *b1 = new Button{model->getSize().first/2 - 100 , 550, 200, 50, 0, "Retour", returnPage, & model->getApp(), button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        Text *bonus = new Text{model->getSize().first/2 - 250, 100, 500, 70, 0, "Bonus", 30, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 1, 0};
        Bonus *coin = new Bonus{model->getSize().first/2 - 230, 170, 40, 40, 0, 0, 0, 0, 0, 0};
        Text *coinDes = new Text{model->getSize().first/2 - 170, 180, 0, 0, 0, "Piece : Augmente votre score de 1000", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0};

        model->getImages().push_back(std::make_pair(1, fond));
        model->getImages().push_back(std::make_pair(1, textBox));
        model->getTexts().push_back(std::make_pair(1, bonus));
        model->getBonus().push_back(std::make_pair(1, coin));
        model->getButtons().push_back(std::make_pair(1, b1));
        model->getTexts().push_back(std::make_pair(1, coinDes));
        break;
    }
    case menuPage::SETTINGS :
    {
        Text *settings = new Text{model->getSize().first/2 - 250, 100, 500, 70, 0, "Options", 30, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 1, 0};
        Image *fond = new Image{0, 0, model->getSize().first, model->getSize().second, "FOND.png", 1, 0, 0};
        Image *textBox = new Image{model->getSize().first/2 - 250, 100, 500, 400, "textBox.png", 2, 0, 0};
        Button *b1 = new Button{model->getSize().first/2 - 100, 550, 200, 50, 0, "Retour", returnPage, & model->getApp(), button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        Button *b2 = new Button{model->getSize().first / 2 - 50, 180, 25, 25, 0, "", menuPage::SETTINGS, & model->getApp(), button_type::RADIO_BUTTON};
        b2->addAction(button_action::SET_FULL_SCREEN);
        b2->setId(button_id::FULL_SCREEN_BUTTON);
        Text *fullScreen = new Text{model->getSize().first/2 - 170, 180, 0, 0, 0, "Plein ecran : ", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0};

        model->getTexts().push_back(std::make_pair(1, settings));
        model->getImages().push_back(std::make_pair(1, fond));
        model->getImages().push_back(std::make_pair(1, textBox));
        model->getTexts().push_back(std::make_pair(1, fullScreen));
        model->getButtons().push_back(std::make_pair(1, b1));
        model->getButtons().push_back(std::make_pair(1, b2));
        break;
    }
    case menuPage::PAUSE :
    {
        Text *pause = new Text{0, 100, MODEL_SIZE_W, 50, 0, "PAUSE", 20, "score.ttf", ColorRGBA::White, text_effect::NOTHING, 20, 1, 0};
        Button *b1 = new Button{model->getSize().first/2 - 100, 550, 200, 50, 0, "Reprendre", returnPage, & model->getApp(), button_type::TEXT_BUTTON};
        b1->addAction(button_action::RESUME_GAME);

        model->getTexts().push_back(std::make_pair(1, pause));
        model->getButtons().push_back(std::make_pair(1, b1));
        break;
    }
    default:
        break;
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

void Menu::exitApp()
{
    m_exitApp = 1;
}
