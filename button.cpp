#include "button.h"
#include "app.h"

Button::Button(float x, float y, float width, float height, float rotation, std::string text, int destinationPage, App *m, int type, bool isClickable): Element::Element{x, y, width, height, rotation}, m_text{text}, m_type{type}, m_isClickable{isClickable}, m_isOn{0}, m_isSelected{0}, m_destinationPage{destinationPage}, m_app{m}, m_actions{}
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

int Button::getType() const
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

bool Button::isSelected() const
{
    return m_isSelected;
}

void Button::setSelected(bool selected)
{
    m_isSelected = selected;
}

void Button::setText(std::string text)
{
    m_text = text;
}

void Button::addAction(int action)
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
            m_app->getMenuModel().exitApp();
            break;
        case button_action::SET_FULL_SCREEN:
            m_app->getSettings().m_isFullScreen = !m_app->getSettings().m_isFullScreen;
            m_isOn = m_app->getSettings().m_isFullScreen;
            break;
        case button_action::RESUME_GAME:
            m_app->getGameModel().setPause(0);
            break;
        case button_action::RESET_GAME:
            m_app->getGameModel().resetGame();
            break;
        case button_action::SET_SELECTED:
            if (m_app->getGameModel().searchElementById(m_id))
            {
                for (std::pair<bool, Button*> b : m_app->getGameModel().getButtons())
                {
                    b.second->setSelected(0);
                }
                m_isSelected = true;
            } else if (m_app->getMenuModel().searchElementById(m_id))
            {
                for (std::pair<bool, Button*> b : m_app->getMenuModel().getButtons())
                {
                    b.second->setSelected(0);
                }
                m_isSelected = true;
            }
            if (m_app->getMenuModel().getActivePage() == menuPage::SELECT_SAVEFILE && m_type == button_type::SAVE_BUTTON)
            {
                for (std::pair <bool, Button*> b: m_app->getMenuModel().getButtons())
                {
                    if (b.second->getId() == button_id::LOAD_SAVE_BUTTON)
                    {
                        if (Player::isActive(m_id - button_id::SELECT_SAVE_1) == true)
                        {
                            b.second->setText("Charger");
                        } else {
                            b.second->setText("Nouveau");
                        }
                    }
                }
            }
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
