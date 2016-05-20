#include "bonus.h"

Bonus::Bonus(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod, int type)
    : MovableElement{x, y, w, h, rotation, mx, my, rotationMovement, movePeriod}, m_type{type}
{

}

std::string Bonus::getClassName() const
{
    return "Bonus";
}

int Bonus::getType() const
{
    return m_type ;
}
