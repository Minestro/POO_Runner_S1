#include "element.h"

Element::Element(float x, float y, float w, float h): m_position{x, y}, m_size{w, h}
{

}

std::pair<float, float> Element::getSize() const
{
    return m_size;
}
std::pair<float, float> Element::getPosition() const
{
    return m_position;
}

void Element::setSize(float w, float h)
{
    m_size.first = w;
    m_size.second = h;
}
