#include "element.h"

Element::Element(float x, float y, float w, float h, float rotation): m_position{x, y}, m_size{w, h}, m_rotation{rotation}
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
void Element::setPosition(float x, float y)
{
    m_position.first=x;
    m_position.second=y;
}

//------------------------------------------------------------------------------
// Input:   el : second élement avec lequel on veut tester la collision
// Output:  Rien
// Return:  Booléen
// Purpose: Fonction qui renvoie si deux élements sont en collision
//------------------------------------------------------------------------------
bool Element::collision(const Element *el) const
{
    return ((el->getPosition().first < m_position.first + m_size.first && el->getPosition().first + el->getSize().first > m_position.first) && (el->getPosition().second < m_position.second + m_size.second && el->getPosition().second + el->getSize().second > m_position.second));
}

std::pair<float, float> Element::getPixelSpeed() const
{
    return (std::make_pair<float, float>(0.0, 0.0));
}

float Element::getRotateAngle() const
{
    return m_rotation;
}
