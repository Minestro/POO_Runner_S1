#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include <math.h>
#include "const.h"

struct ColorRGBA
{
    ColorRGBA(unsigned int cr, unsigned int cg, unsigned int cb, unsigned int alpha = 255);
    unsigned int r, g, b, a;
    static const ColorRGBA White;
    static const ColorRGBA Black;
};

class Element
{
protected:
    std::pair <float, float> m_position; //first : x, second : y
    std::pair <float, float> m_size;  //first : w, second : h
    float m_rotation;
public:
    Element()= default;
    Element(float x, float y, float w, float h, float rotation);
    virtual ~Element() = default;
    virtual std::string getClassName() const=0;
    std::pair<float, float> getSize() const;
    std::pair<float, float> getPosition() const;
    float getRotateAngle() const;
    void setSize(float w, float h);
    void setPosition(float x, float y);
    bool collision(const Element *el) const;
    virtual std::pair<float, float> getPixelSpeed() const;
};

#endif // ELEMENT_H
