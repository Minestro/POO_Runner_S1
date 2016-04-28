#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include "const.h"

class Element
{
protected:
    std::pair <float, float> m_position; //first : x, second : y
    std::pair <float, float> m_size;  //first : w, second : h
public:
    Element()= default;
    Element(float x, float y, float w, float h);
    virtual ~Element() = default;
    virtual std::string getClassName() const=0;
    std::pair<float, float> getSize() const;
    void setSize(float w, float h);
    void setPosition(float x, float y);
    std::pair<float, float> getPosition() const;
    bool collision(const Element *el) const;
    virtual std::pair<float, float> getPixelSpeed() const;
};

#endif // ELEMENT_H
