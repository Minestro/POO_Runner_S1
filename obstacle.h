#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "movableelement.h"

class Obstacle: public MovableElement
{
private:
    unsigned int m_dammage; //Le nombre de points de vie qu'enlève l'obstacle.
    unsigned int m_type;
public:
    unsigned int getDammage() const;
    unsigned int getType() const;
};

#endif // OBSTACLE_H
