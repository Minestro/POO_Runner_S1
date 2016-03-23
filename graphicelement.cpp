#include "graphicelement.h"

GraphicElement::GraphicElement(float width, float height, float x, float y, const sf::Texture &texture) : sf::Sprite::Sprite{}, m_size{width, height}
{
    setTexture(texture);
    setPosition(x, y);
}

void GraphicElement::rescale()
{
    sf::FloatRect bb = this->getLocalBounds();
    int width_factor = m_size.first / bb.width;
    int height_factor = m_size.second / bb.height;
    this->setScale(width_factor, height_factor);
}

void GraphicElement::setSize(float width, float height)
{
   m_size.first = width;
   m_size.second = height;
}


