#include "circleshapeelement.h"

CircleShapeElement::CircleShapeElement(unsigned int zIndex, float width, float height, float x, float y, sf::Color color): GraphicElement::GraphicElement{zIndex}, sf::CircleShape::CircleShape{(width+height)/4}
{
    setOrigin(0, 0);
    setPosition(x, y);
    setSize(width, height);
    setFillColor(color);
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
}

std::pair<float, float> CircleShapeElement::getSize() const
{
    return {sf::CircleShape::getGlobalBounds().width * getScale().x, sf::CircleShape::getGlobalBounds().height * getScale().y};
}

std::pair<float, float> CircleShapeElement::getPosition() const
{
    return {CircleShape::getPosition().x, CircleShape::getPosition().y};
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
    sf::CircleShape::setPosition(x, y);
}

void CircleShapeElement::refresh(const Element *el, Model *model)
{
    (void) model;
    setSize(el->getSize().first, el->getSize().second);
    setPosition(el->getPosition().first, el->getPosition().second);
}