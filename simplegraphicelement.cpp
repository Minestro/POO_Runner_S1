#include "simplegraphicelement.h"

SimpleGraphicElement::SimpleGraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture): GraphicElement{zIndex, width, height, x, y, texture}
{

}

SimpleGraphicElement::SimpleGraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, const sf::IntRect &textRect) : GraphicElement{zIndex, width, height, x, y, texture, textRect}
{

}

std::string SimpleGraphicElement::getClassName() const
{
    return "SimpleGraphicElement";
}
