#include "obstacle.h"

Obstacle::Obstacle(float x, float y, float w, float h, float mx, float my, int movePeriod,unsigned int dammage, unsigned int type)
: MovableElement{x,y,w,h,mx,my,movePeriod}, m_dammage{dammage}, m_type{type}
{

}
unsigned int Obstacle::getDammage() const
{
    return m_dammage;
}

unsigned int Obstacle::getType() const
{
    return m_type;
}

std::string Obstacle::getClassName() const
{
    return "Obstacle";
}
