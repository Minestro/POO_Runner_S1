#include "element.h"

Element::Element(float x, float y, float w, float h, unsigned int spriteID): m_position{x, y}, m_size{w, h}, m_spriteID{spriteID}
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

unsigned int Element::getSpriteID() const
{
    return m_spriteID;
}
