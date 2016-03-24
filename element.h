#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>

class Element
{
private:
    std::pair <float, float> m_size;  //first : w, second : h
    std::pair <float, float> m_position; //first : x, second : y
public:
    Element();
    std::pair<float, float> getSize() const;
    std::pair<float, float> getPosition() const;
};

#endif // ELEMENT_H
