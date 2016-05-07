#include "menu.h"

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
        Button *b1 = new Button{GAME_SIZE_W/2 - 100, 50, 200, 50, 0, "Jouer", menuPage::ESCAPE_MENU, this, button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        Button *b2 = new Button{GAME_SIZE_W/2 - 100, 150, 200, 50, 0, "Explication", menuPage::EXPLICATION, this, button_type::TEXT_BUTTON};
        b2->addAction(button_action::CHANGE_PAGE);

         m_buttons.push_back(std::make_pair(1, b1));
         m_buttons.push_back(std::make_pair(1, b2));

         m_backgrounds.push_back(std::make_pair(1, new Background{"menuBackground.png", 1, 0, 0}));
        break;
    }
    case menuPage::PRE_MENU :
    {
        m_backgrounds.push_back(std::make_pair(1, new Background{"FOND2.png", 1, 0.5, 1, m_backgroundMovePeriod}));
        m_backgrounds.push_back(std::make_pair(1, new Background{"FOND1.png", 2, 1.0, 1, m_backgroundMovePeriod}));
        m_texts.push_back(std::make_pair(1, new Text{0, 600, GAME_SIZE_W, 50, 0, "Appuyez sur une touche pour continuer", 20, "score.ttf", 255, 255, 255, text_effect::BREATH, 20, 1, 0}));
        break;
    }
    case menuPage::EXPLICATION :
    {
        m_backgrounds.push_back(std::make_pair(1, new Background{"FOND.png", 1, 0, 0}));
        Button *b1 = new Button{GAME_SIZE_W/2 - 200, 50, 200, 50, 0, "Retour", menuPage::HOME, this, button_type::TEXT_BUTTON};
        b1->addAction(button_action::CHANGE_PAGE);
        m_buttons.push_back(std::make_pair(1, b1));
        break;
     }

    default:
        break;
    }
}

void Menu::refresh()
{
    for (unsigned int i=0; i<m_backgrounds.size(); i++)
    {
        m_backgrounds[i].second->setMovePeriod(m_backgroundMovePeriod);
        m_backgrounds[i].second->move();
    }
}

int Menu::getActivePage() const
{
    return m_activePage;
}
