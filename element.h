#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "graphicelement.h"

class Element
{
private:
    std::pair <float, float> m_position; //first : x, second : y
    std::pair <float, float> m_size;  //first : w, second : h
public:
    Element()= default;
    Element(float x, float y, float w, float h, unsigned int spriteID, unsigned int zIndex = 0, bool isAnimated = false);
    std::pair<float, float> getSize() const;
    std::pair<float, float> getPosition() const;
};

#endif // ELEMENT_H
