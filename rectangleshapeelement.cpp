#include "rectangleshapeelement.h"

RectangleShapeElement::RectangleShapeElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, sf::Color color): GraphicElement::GraphicElement{zIndex}, RectangleShape::RectangleShape{sf::Vector2f{width, height}}
{
    setPosition(x, y);
    setFillColor(color);
    setRotateAngle(rotateAngle);
}

void RectangleShapeElement::setSize(float width, float height)
{
    RectangleShape::setSize(sf::Vector2f{width, height});
}

void RectangleShapeElement::setPosition(float x, float y)
{
    sf::RectangleShape::setPosition(x, y);
}

void RectangleShapeElement::setRotateAngle(float angle)
{
    setRotation(angle);
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

void RectangleShapeElement::refresh(const Element *el, Model *model)
{
    (void) model;
    setPosition(el->getPosition().first, el->getPosition().second);
    setSize(el->getSize().first, el->getSize().second);
    setRotateAngle(el->getRotateAngle());
}
