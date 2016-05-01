#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "movableelement.h"

enum obstacle_type{MINE};
enum obstacle_state{ACTIVE, EXPLODE};

class Obstacle: public MovableElement
{
private:
    unsigned int m_dammage; //Le nombre de points de vie qu'enlève l'obstacle.
    obstacle_state m_state;
    obstacle_type m_type;
public:
    Obstacle(float x, float y, float w, float h, float mx, float my, int movePeriod,unsigned int dammage, obstacle_type type);
    virtual ~Obstacle() = default;
    void setState(obstacle_state state);
    unsigned int getDammage() const;
    std::string getClassName() const;
    obstacle_state getState() const;
    obstacle_type getType() const;
};

#endif // OBSTACLE_H
