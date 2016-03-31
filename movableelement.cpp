#include "movableelement.h"

MovableElement::MovableElement(float x, float y, float w, float h, float mx, float my): Element{x, y, w, h}, m_movement{mx, my}
{

}

std::string MovableElement::getClassName() const
{
    return "MovableElement";
}

void MovableElement::move()
{
    m_position.first += m_movement.first;
    m_position.second += m_movement.second;
}
