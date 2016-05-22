#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include <math.h>
#include "const.h"

#define IDNOTSET 0

enum pointsName{UL, UR, DL, DR};

struct ColorRGBA
{
    ColorRGBA();
    ColorRGBA(unsigned int cr, unsigned int cg, unsigned int cb, unsigned int alpha = 255);
    unsigned int r, g, b, a;
    static const ColorRGBA White;
    static const ColorRGBA Black;
    static const ColorRGBA Red;
};

class Element
{
protected:
    Element(float x, float y, float w, float h, float rotation, unsigned long int id = 0);
    unsigned long int m_id;
    std::pair <float, float> m_position; //first : x, second : y
    std::pair <float, float> m_size;  //first : w, second : h
    float m_rotation;
public:
    virtual ~Element() = default;
    virtual std::string getClassName() const=0;
    std::pair<float, float> getSize() const;
    std::pair<float, float> getPosition() const;
    float getRotateAngle() const;
    unsigned long int getId() const;
    std::vector<std::pair<float, float> > getPointsAfterRotation() const;
    void setSize(float w, float h);
    void setPosition(float x, float y);
    void setId(unsigned long int id);
    bool collision(const Element *el) const;
    virtual std::pair<float, float> getPixelSpeed() const;
};

#endif // ELEMENT_H
