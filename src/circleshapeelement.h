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

#ifndef CIRCLESHAPEELEMENT_H
#define CIRCLESHAPEELEMENT_H

#include "graphicelement.h"

class CircleShapeElement: public GraphicElement, public sf::CircleShape
{
private:
    void rescale(float width, float height);
public:
    CircleShapeElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Color color = sf::Color::Black);
    virtual ~CircleShapeElement() = default;
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const override;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderTarget *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // CIRCLESHAPEELEMENT_H
