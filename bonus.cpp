#include "bonus.h"

Bonus::Bonus(float x, float y, float w, float h, float mx, float my, int movePeriod, bonus_type type)
    : MovableElement{x,y,w,h,mx,my,movePeriod}, m_type{type}
{

}

std::string Bonus::getClassName() const
{
    return "Bonus";
}

bonus_type Bonus::getType() const
{
    return m_type ;
}
