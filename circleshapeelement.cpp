#include "circleshapeelement.h"

CircleShapeElement::CircleShapeElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, sf::Color color): GraphicElement::GraphicElement{zIndex}, sf::CircleShape::CircleShape{(width+height)/4}
{
    setSize(width, height);
    setOrigin(width/2, height/2);
    setFillColor(color);
    setPosition(x, y);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
    setRotation(rotateAngle);
}

void CircleShapeElement::rescale(float width, float height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = width / bb.width;
    float height_factor = height / bb.height;
    setScale(width_factor, height_factor);
}

void CircleShapeElement::setSize(float width, float height)
{
    setRadius((width+height)/4);
    rescale(width, height);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
}

std::pair<float, float> CircleShapeElement::getSize() const
{
    return {sf::CircleShape::getGlobalBounds().width, sf::CircleShape::getGlobalBounds().height};
}

std::pair<float, float> CircleShapeElement::getPosition() const
{
    return {CircleShape::getPosition().x - getOrigin().x * getScale().x, CircleShape::getPosition().y - getOrigin().y * getScale().y};
}

std::string CircleShapeElement::getClassName() const
{
    return "CircleShapeElement";
}

void CircleShapeElement::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}

void CircleShapeElement::setPosition(float x, float y)
{
    sf::CircleShape::setPosition(x + getOrigin().x * getScale().x, y + getOrigin().y * getScale().y);
}

void CircleShapeElement::refresh(const Element *el, Model *model)
{
    (void) model;
    setSize(el->getSize().first, el->getSize().second);
    setPosition(el->getPosition().first, el->getPosition().second);
    setRotation(el->getRotateAngle());
}
