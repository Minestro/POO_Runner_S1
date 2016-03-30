#include "movableelement.h"

MovableElement::MovableElement(float x, float y, float w, float h, float mx, float my): Element::Element{x, y, w, h}, m_movement{mx, my}
{

}

std::string MovableElement::getClassName() const
{
    return "MovableElement";
}
