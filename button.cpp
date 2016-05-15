#include "button.h"
#include "app.h"

Button::Button(float x, float y, float width, float height, float rotation, std::string text, int destinationPage, App *m, button_type type, bool isClickable): Element::Element{x, y, width, height, rotation}, m_text{text}, m_type{type}, m_isClickable{isClickable}, m_isOn{0}, m_destinationPage{destinationPage}, m_app{m}, m_actions{}
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
    return m_isClickable;
}

bool Button::isOn() const
{
    bool isOn = false;
    switch (m_id)
    {
    case button_id::FULL_SCREEN_BUTTON:
        isOn = m_app->getSettings().m_isFullScreen;
        break;
    default:
        break;
    }
    return isOn;
}

void Button::setIsOn(bool on)
{
    m_isOn = on;
}

void Button::addAction(button_action action)
{
    m_actions.push_back(action);
}

//------------------------------------------------------------------------------
// Input:   x : coordonnées de la souris en x
//          y : coordonnées de la souris en y
// Output:  Rien
// Return:  Booléen
// Purpose: Fonction qui renvoie si le bouton est survolé par la souris
//------------------------------------------------------------------------------
bool Button::isHover(int x, int y) const
{
    return (x < m_position.first + m_size.first && x > m_position.first && y < m_position.second + m_size.second && y > m_position.second);
}

void Button::onClick()
{
    for (unsigned int i=0; i<m_actions.size(); i++)
    {
        switch (m_actions[i])
        {
        case button_action::CHANGE_PAGE:
            Button::changePage(this, *m_app);
            break;
        case button_action::EXIT_APP:
            m_app->stop();
            break;
        case button_action::SET_FULL_SCREEN:
            m_app->getSettings().m_isFullScreen = !m_app->getSettings().m_isFullScreen;
            m_isOn = m_app->getSettings().m_isFullScreen;
            break;
        default:
            break;
        }
    }
}

int Button::getDestinationPage() const
{
    return m_destinationPage;
}

void Button::changePage(const Button *sender, App &app)
{
    app.getMenuModel().setPage(sender->getDestinationPage());
}
