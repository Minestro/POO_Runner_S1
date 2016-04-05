#include "movableelement.h"

MovableElement::MovableElement(float x, float y, float w, float h, float mx, float my, int movePeriod): Element{x, y, w, h}, m_movement{mx, my}, m_lastMoveCall{}, m_movePeriod{movePeriod}
{

}

std::string MovableElement::getClassName() const
{
    return "MovableElement";
}

void MovableElement::move()
{
    if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-m_lastMoveCall).count() > m_movePeriod)
    {
        m_position.first += m_movement.first;
        m_position.second += m_movement.second;
        m_lastMoveCall = std::chrono::system_clock::now();
    }
}
