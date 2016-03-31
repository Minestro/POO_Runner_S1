#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

#include "element.h"
#include <vector>

class MovableElement: public Element
{
protected:
    std::pair <float, float> m_movement; //first : x, second : y

public:
    MovableElement(float x, float y, float w, float h, float mx, float my);
    virtual std::string getClassName() const =0;
    void move() const;
};

#endif // MOVABLEELEMENT_H
