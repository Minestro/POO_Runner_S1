#include "menu.h"

Menu::Menu(float width, float height, int activePage): Model::Model{width, height}, m_activePage{activePage}
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
    switch (m_activePage)
    {
    case menuPage::HOME :
         m_buttons.push_back(std::make_pair(1, new Button{50, 50, 200, 50, "test", menuPage::ESCAPE_MENU, this, button_type::TEXT_BUTTON}));
        break;
    default:
        break;
    }
}

void Menu::refresh()
{

}

int Menu::getActivePage() const
{
    return m_activePage;
}
