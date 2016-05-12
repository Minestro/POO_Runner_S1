#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height, int activePage): Model::Model{width, height}, m_activePage{activePage}, m_backgroundMovePeriod{STARTSPEEDPERIODGAME}
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
    refreshContent();
}

void Menu::refreshContent()
{
    clearAll();

    switch (m_activePage)
    {
    case menuPage::HOME :
    {
        Button *b1 = new Button{GAME_SIZE_W/2 - 100, 150, 200, 50, 0, "Jouer", menuPage::ESCAPE_MENU, this, button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        Button *b2 = new Button{GAME_SIZE_W/2 - 100, 250, 200, 50, 0, "Regles", menuPage::RULES, this, button_type::TEXT_BUTTON};
        b2->addAction(button_action::CHANGE_PAGE);

         m_buttons.push_back(std::make_pair(1, b1));
         m_buttons.push_back(std::make_pair(1, b2));

         m_images.push_back(std::make_pair(1, new Image{0, 0, GAME_SIZE_W, GAME_SIZE_H, "menuBackground.png", 1, 0, 0}));
        break;
    }
    case menuPage::PRE_MENU :
    {
        m_images.push_back(std::make_pair(1, new Image{0, 0, GAME_SIZE_W, GAME_SIZE_H, "FOND2.png", 1, 0.5, 1, m_backgroundMovePeriod}));
        m_images.push_back(std::make_pair(1, new Image{0, 0, GAME_SIZE_W, GAME_SIZE_H, "FOND1.png", 2, 1.0, 1, m_backgroundMovePeriod}));
        m_texts.push_back(std::make_pair(1, new Text{0, 600, GAME_SIZE_W, 50, 0, "Appuyez sur une touche pour continuer", 20, "score.ttf", ColorRGBA::White,text_effect::BREATH, 20, 1, 0}));
        break;
    }
    case menuPage::RULES :
    {
        m_images.push_back(std::make_pair(1, new Image{0, 0, GAME_SIZE_W, GAME_SIZE_H, "FOND.png", 1, 0, 0}));
        m_images.push_back(std::make_pair(1, new Image{GAME_SIZE_W/2 - 250, 100, 500, 400, "textBox.png", 2, 0, 0}));
        m_texts.push_back(std::make_pair(1, new Text{GAME_SIZE_W/2 - 250, 100, 500, 70, 0, "Regles", 30, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 1, 0}));
        m_texts.push_back(std::make_pair(1, new Text{GAME_SIZE_W/2 - 230, 170, 460, 150, 0, "Pilotez l'avion le plus loin possible en evitant les obstacles et en ramassant un maximum de pieces possible !", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 1, 1}));
        m_images.push_back(std::make_pair(1, new Image{GAME_SIZE_W/2 - 230, 250, 40, 40, "leftKey.png", 3, 0, 0}));
        m_images.push_back(std::make_pair(1, new Image{GAME_SIZE_W/2 - 230, 310, 40, 40, "rightKey.png", 3, 0, 0}));
        m_images.push_back(std::make_pair(1, new Image{GAME_SIZE_W/2 - 230, 370, 40, 40, "upKey.png", 3, 0, 0}));
        m_texts.push_back(std::make_pair(1, new Text{GAME_SIZE_W/2 - 170, 250, 0, 0, 0, "Reculer", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0}));
        m_texts.push_back(std::make_pair(1, new Text{GAME_SIZE_W/2 - 170, 310, 0, 0, 0, "Avancer", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0}));
        m_texts.push_back(std::make_pair(1, new Text{GAME_SIZE_W/2 - 170, 370, 0, 0, 0, "Monter", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0}));
        Button *b1 = new Button{GAME_SIZE_W/2 - 250, 550, 200, 50, 0, "Retour", menuPage::HOME, this, button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        Button *b2 = new Button{GAME_SIZE_W/2 + 50 , 550, 200, 50, 0, "Liste des objets", menuPage::BONUSLIST, this, button_type::TEXT_BUTTON};
        b2->addAction(button_action::CHANGE_PAGE);
        m_buttons.push_back(std::make_pair(1, b1));
        m_buttons.push_back(std::make_pair(1, b2));
        break;
     }
    case menuPage::BONUSLIST :
    {
        m_images.push_back(std::make_pair(1, new Image{0, 0, GAME_SIZE_W, GAME_SIZE_H, "FOND.png", 1, 0, 0}));
        m_images.push_back(std::make_pair(1, new Image{GAME_SIZE_W/2 - 250, 100, 500, 400, "textBox.png", 2, 0, 0}));
        Button *b1 = new Button{GAME_SIZE_W/2 - 100 , 550, 200, 50, 0, "Retour", menuPage::HOME, this, button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        m_texts.push_back(std::make_pair(1, new Text{GAME_SIZE_W/2 - 250, 100, 500, 70, 0, "Bonus", 30, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 1, 0}));
        m_bonus.push_back(std::make_pair(1, new Bonus{GAME_SIZE_W/2 - 230, 170, 40, 40, 0, 0, 0, 0, 0, 0}));
        m_buttons.push_back(std::make_pair(1, b1));
        m_texts.push_back(std::make_pair(1, new Text{GAME_SIZE_W/2 - 170, 180, 0, 0, 0, "Piece : Augmente votre score de 1000", 20, "score.ttf" , ColorRGBA::Black, text_effect::NOTHING, 0, 0, 0}));

    }

    default:
        break;
    }
}

void Menu::refresh()
{
    for (unsigned int i=0; i<m_images.size(); i++)
    {
        m_images[i].second->setMovePeriod(m_backgroundMovePeriod);
        m_images[i].second->move();
    }
}

int Menu::getActivePage() const
{
    return m_activePage;
}
