#include "menu.h"

Menu::Menu(float width, float height, int activePage): Model::Model{width, height}, m_activePage{activePage}, m_backgroundMovePeriod{STARTSPEEDPERIODGAME}
{
    changePage(activePage);
}

std::pair<float, float> Menu::getCharacterSpeed(const GameCharacter *gc) const
{
    return (gc->getPixelSpeed());
}

void Menu::changePage(int page)
{
    m_activePage = page;
    for (unsigned int i = 0; i<m_backgrounds.size(); i++)
    {
        m_deletedElements.push_back(m_backgrounds[i].second);
    }
    m_backgrounds.clear();
    for (unsigned int i = 0; i<m_bonus.size(); i++)
    {
        m_deletedElements.push_back(m_bonus[i].second);
    }
    m_bonus.clear();
    for (unsigned int i = 0; i<m_buttons.size(); i++)
    {
        m_deletedElements.push_back(m_buttons[i].second);
    }
    m_buttons.clear();
    for (unsigned int i = 0; i<m_characters.size(); i++)
    {
        m_deletedElements.push_back(m_characters[i].second);
    }
    m_characters.clear();
    for (unsigned int i = 0; i<m_obstacles.size(); i++)
    {
        m_deletedElements.push_back(m_obstacles[i].second);
    }
    m_obstacles.clear();
    switch (m_activePage)
    {
    case menuPage::HOME :
         m_buttons.push_back(std::make_pair(1, new Button{GAME_SIZE_W/2 - 100, 50, 200, 50, "Jouer", menuPage::ESCAPE_MENU, this, button_type::TEXT_BUTTON}));
         m_backgrounds.push_back(std::make_pair(1, new Background{"city_2.png", 1, 1.5, 1, 0}));
         m_backgrounds.push_back(std::make_pair(1, new Background{"city_1.png", 2, 1.0, 1, 0}));
        break;
    default:
        break;
    }
}

void Menu::refresh()
{
    for (unsigned int i=0; i<m_backgrounds.size(); i++)
    {
        m_backgrounds[i].second->setMovePeriod(m_backgrounds[i].second->getCoefSpeed() * m_backgroundMovePeriod);
        m_backgrounds[i].second->move();
    }
}

int Menu::getActivePage() const
{
    return m_activePage;
}
