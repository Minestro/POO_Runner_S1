#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "movableelement.h"

enum obstacle_type{MINE};
enum obstacle_state{ACTIVE, EXPLODE};

class Obstacle: public MovableElement
{
private:
    unsigned int m_dammage; //Le nombre de points de vie qu'enlève l'obstacle.
    int m_state;
    int m_type;
public:
    Obstacle(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod,unsigned int dammage, int type);
    virtual ~Obstacle() = default;
    void setState(int state);
    unsigned int getDammage() const;
    std::string getClassName() const;
    int getState() const;
    int getType() const;
};

#endif // OBSTACLE_H
