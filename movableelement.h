#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

#include "element.h"
#include <vector>

class MovableElement: public Element
{
protected:
    std::pair <float, float> m_movement; //first : x, second : y

public:
    void move() const;
};

#endif // MOVABLEELEMENT_H
