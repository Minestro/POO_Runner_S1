#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "movableelement.h"

class Obstacle:MovableElement
{
private:
    unsigned int m_dammage; //Le nombre de points de vie qu'enlève l'obstacle.
public:
    unsigned int getDammage() const;
};

#endif // OBSTACLE_H
