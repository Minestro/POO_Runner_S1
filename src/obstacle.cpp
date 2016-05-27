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

#include "obstacle.h"

Obstacle::Obstacle(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod, unsigned int dammage, int type)
    : MovableElement{x, y, w, h, rotation, mx, my, rotationMovement, movePeriod}, m_dammage{dammage}, m_state{obstacle_state::ACTIVE}, m_type{type}
{

}

unsigned int Obstacle::getDammage() const
{
    return m_dammage;
}

std::string Obstacle::getClassName() const
{
    return "Obstacle";
}

void Obstacle::setState(int state)
{
    m_state = state;
}

int Obstacle::getState() const
{
    return m_state;
}

int Obstacle::getType() const
{
    return m_type;
}
