#include "menu.h"

Menu::Menu(): m_size{MENU_SIZE_W, MENU_SIZE_H},  m_activePage{0}
{

}

std::pair<float, float> Menu::getCharacterSpeed(const GameCharacter *gc) const
{
    return (gc->getPixelSpeed());
}
