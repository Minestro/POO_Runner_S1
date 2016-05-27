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
