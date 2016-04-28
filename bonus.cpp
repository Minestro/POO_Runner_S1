#include "bonus.h"

Bonus::Bonus(float x, float y, float w, float h, float mx, float my, int movePeriod, bonus_state type)
    : MovableElement{x,y,w,h,mx,my,movePeriod}, m_type{type}
{

}

std::string Bonus::getClassName() const
{
    return "Bonus";
}
