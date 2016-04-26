#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "movableelement.h"

enum obstacle_state{ACTIVE, EXPLODE};

class Obstacle: public MovableElement
{
private:
    unsigned int m_dammage; //Le nombre de points de vie qu'enlève l'obstacle.
    unsigned int m_type;
    obstacle_state m_state;
public:
    Obstacle(float x, float y, float w, float h, float mx, float my, int movePeriod,unsigned int dammage, unsigned int type);
    virtual ~Obstacle() = default;
    void setState(obstacle_state state);
    unsigned int getDammage() const;
    unsigned int getType() const;
    std::string getClassName() const;
    obstacle_state getState() const;
};

#endif // OBSTACLE_H
