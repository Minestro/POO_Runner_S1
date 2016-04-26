#include "obstacle.h"

Obstacle::Obstacle(float x, float y, float w, float h, float mx, float my, int movePeriod,unsigned int dammage, unsigned int type)
    : MovableElement{x,y,w,h,mx,my,movePeriod}, m_dammage{dammage}, m_type{type}, m_state{obstacle_state::ACTIVE}
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

void Obstacle::setState(obstacle_state state)
{
    m_state = state;
}

obstacle_state Obstacle::getState() const
{
    return m_state;
}
