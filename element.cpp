#include "element.h"

Element::Element(int zIndex, float x, float y, float w, float h, unsigned int spriteID): m_position{x, y}, m_size{w, h}, m_spriteID{spriteID}, m_zIndex{zIndex}
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

unsigned int Element::getzIndex() const
{
    return m_zIndex;
}
