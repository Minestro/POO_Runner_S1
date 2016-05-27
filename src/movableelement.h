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

#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

#include "element.h"
#include "const.h"
#include <chrono>

class MovableElement: public Element
{
protected:
    MovableElement(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod);
    std::pair <float, float> m_movement; //first : x, second : y
    float m_rotationMovement;
    std::chrono::time_point<std::chrono::system_clock> m_lastMoveCall;
    int m_movePeriod;

public:
    virtual ~MovableElement() = default;
    virtual std::string getClassName() const =0;
    virtual void move();
    void setMovePeriod(float movePeriod);
    void setMovement(float dx, float dy);
    std::pair<float, float> getMovement() const;
    std::pair<float, float> getPixelSpeed() const override;
};

#endif // MOVABLEELEMENT_H
