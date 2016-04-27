#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

#include "element.h"
#include "const.h"
#include <chrono>

class MovableElement: public Element
{
protected:
    std::pair <float, float> m_movement; //first : x, second : y
    std::chrono::time_point<std::chrono::system_clock> m_lastMoveCall;
    int m_movePeriod;

public:
    MovableElement(float x, float y, float w, float h, float mx, float my, int movePeriod);
    virtual ~MovableElement() = default;
    virtual std::string getClassName() const =0;
    virtual void move();
    void setMovePeriod(float movePeriod);
    void setMovement(float dx, float dy);
    std::pair<float, float> getPixelSpeed() const override;
};

#endif // MOVABLEELEMENT_H
