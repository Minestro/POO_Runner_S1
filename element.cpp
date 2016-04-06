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

bool Element::collision(const Element *el) const
{
    return ((el->getPosition().first < m_position.first + m_size.first && el->getPosition().first + el->getSize().first > m_position.first) && (el->getPosition().second < m_position.second + m_size.second && el->getPosition().second + el->getSize().second > m_position.second));
}
