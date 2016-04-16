#include "rectangleshapeelement.h"

RectangleShapeElement::RectangleShapeElement(unsigned int zIndex, float width, float height, float x, float y, sf::Color color): GraphicElement::GraphicElement{zIndex}, RectangleShape::RectangleShape{sf::Vector2f{width, height}}
{
    setOrigin(0, 0);
    setPosition(x, y);
    setFillColor(color);
}

void RectangleShapeElement::rescale(float width, float height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = width / bb.width;
    float height_factor = height / bb.height;
    setScale(width_factor, height_factor);
}

void RectangleShapeElement::setSize(float width, float height)
{
    RectangleShape::setSize(sf::Vector2f{width, height});
}

std::pair<float, float> RectangleShapeElement::getSize() const
{
    return {RectangleShape::getSize().x, RectangleShape::getSize().y};
}

std::pair<float, float> RectangleShapeElement::getPosition() const
{
    return {sf::RectangleShape::getPosition().x, sf::RectangleShape::getPosition().y};
}

std::string RectangleShapeElement::getClassName() const
{
    return "RectangleShapeElement";
}

void RectangleShapeElement::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}

void RectangleShapeElement::setPosition(float x, float y)
{
    sf::RectangleShape::setPosition(x, y);
}

void RectangleShapeElement::refresh(const Element *el)
{
    setPosition(el->getPosition().first, el->getPosition().second);
    setSize(el->getSize().first, el->getSize().second);
}
