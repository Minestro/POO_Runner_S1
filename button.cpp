#include "button.h"
#include "menu.h"

Button::Button(float x, float y, float width, float height, std::string text, int destinationPage, Menu *m, button_type type, bool isClickable): Element::Element{x, y, width, height}, m_text{text}, m_type{type}, m_isClickable{isClickable}, m_destinationPage{destinationPage}, m_menu{m}
{

}

std::string Button::getClassName() const
{
    return "Button";
}

std::string Button::getText() const
{
    return m_text;
}

button_type Button::getType() const
{
    return m_type;
}

bool Button::isClickable() const
{
    return isClickable();
}

bool Button::isHover(int x, int y) const
{
    return (x < m_position.first + m_size.first && x > m_position.first && y < m_position.second + m_size.second && y > m_position.second);
}

void Button::onClick()
{
    m_menu->changePage(m_destinationPage);
}
