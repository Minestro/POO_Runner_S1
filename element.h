#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include "graphicelement.h"

class Element
{
private:
    bool m_isAnimated;
    std::pair <float, float> m_position; //first : x, second : y
    std::pair <float, float> m_size;  //first : w, second : h
    unsigned int m_zIndex;
    unsigned int m_spriteID;
public:
    Element()= default;
    Element(float x, float y, float w, float h, unsigned int spriteID, unsigned int zIndex = 0, bool isAnimated = false);
    std::pair<float, float> getSize() const;
    std::pair<float, float> getPosition() const;
    unsigned int getSpriteID() const;
    unsigned int getzIndex() const;
    bool isAnimated() const;
};

#endif // ELEMENT_H
