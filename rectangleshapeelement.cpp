#include "rectangleshapeelement.h"
#include "model.h"

RectangleShapeElement::RectangleShapeElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, sf::Color color): GraphicElement::GraphicElement{zIndex}, RectangleShape::RectangleShape{sf::Vector2f{width, height}}
{
    setPosition(x, y);
    setFillColor(color);
    setRotation(rotateAngle);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
}

void RectangleShapeElement::setSize(float width, float height)
{
    RectangleShape::setSize(sf::Vector2f{width, height});
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
}

void RectangleShapeElement::setPosition(float x, float y)
{
    sf::RectangleShape::setPosition(x + getOrigin().x * getScale().x, y + getOrigin().y * getScale().y);
}

std::pair<float, float> RectangleShapeElement::getSize() const
{
    return {RectangleShape::getSize().x, RectangleShape::getSize().y};
}

std::pair<float, float> RectangleShapeElement::getPosition() const
{
    return {sf::RectangleShape::getPosition().x - getOrigin().x * getScale().x, sf::RectangleShape::getPosition().y - getOrigin().y * getScale().y};
}

std::string RectangleShapeElement::getClassName() const
{
    return "RectangleShapeElement";
}

void RectangleShapeElement::draw(sf::RenderTarget *window) const
{
    window->draw(*this);
}

void RectangleShapeElement::refresh(const Element *el, Model *model)
{
    (void) model;
    setPosition(el->getPosition().first, el->getPosition().second);
    setSize(el->getSize().first, el->getSize().second);
    setRotation(el->getRotateAngle());
}
