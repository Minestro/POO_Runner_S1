#include "rectangleshapeelement.h"

RectangleShapeElement::RectangleShapeElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, sf::Color color): GraphicElement::GraphicElement{zIndex}, RectangleShape::RectangleShape{sf::Vector2f{width, height}}
{
    setOrigin(width/2, height/2);
    setPosition(x, y);
    setFillColor(color);
    setRotateAngle(rotateAngle);
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
    setOrigin(sf::RectangleShape::getSize().x / 2, sf::RectangleShape::getSize().y / 2);
}

void RectangleShapeElement::setPosition(float x, float y)
{
    sf::RectangleShape::setPosition(x + getOrigin().x * getScale().x, y + getOrigin().y * getScale().y);
}

void RectangleShapeElement::setRotateAngle(float angle)
{
    setRotation(angle);
}

std::pair<float, float> RectangleShapeElement::getSize() const
{
    return {RectangleShape::getSize().x * getScale().x, RectangleShape::getSize().y * getScale().y};
}

std::pair<float, float> RectangleShapeElement::getPosition() const
{
    return {sf::RectangleShape::getPosition().x - getScale().x, sf::RectangleShape::getPosition().y - getScale().y};
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
