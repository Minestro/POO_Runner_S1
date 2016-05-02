#include "bonus.h"

Bonus::Bonus(float x, float y, float w, float h, float mx, float my, int movePeriod, int type)
    : MovableElement{x,y,w,h,mx,my,movePeriod}, m_type{type}
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
