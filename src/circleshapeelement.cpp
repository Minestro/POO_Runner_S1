/*Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#include "circleshapeelement.h"
#include "model.h"

CircleShapeElement::CircleShapeElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Color color): GraphicElement::GraphicElement{zIndex}, sf::CircleShape::CircleShape{(width+height)/4}
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

void CircleShapeElement::draw(sf::RenderTarget *window) const
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
