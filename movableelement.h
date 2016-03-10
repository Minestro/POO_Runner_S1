#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

#include <vector>

class MovableElement
{
private:
    std::pair <float, float> m_size;  //first : w, second : h
    std::pair <float, float> m_position; //first : x, second : y
    std::pair <float, float> m_movement; //first : x, second : y

public:
    void move() const;
};

#endif // MOVABLEELEMENT_H
