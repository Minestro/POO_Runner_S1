#include "obstacle.h"

Obstacle::Obstacle(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod, unsigned int dammage, int type)
    : MovableElement{x, y, w, h, rotation, mx, my, rotationMovement, movePeriod}, m_dammage{dammage}, m_state{obstacle_state::ACTIVE}, m_type{type}
{

}
unsigned int Obstacle::getDammage() const
{
    return m_dammage;
}

std::string Obstacle::getClassName() const
{
    return "Obstacle";
}

void Obstacle::setState(int state)
{
    m_state = state;
}

int Obstacle::getState() const
{
    return m_state;
}

int Obstacle::getType() const
{
    return m_type;
}
