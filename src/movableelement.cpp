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

#include "movableelement.h"

MovableElement::MovableElement(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod): Element{x, y, w, h, rotation}, m_movement{mx, my}, m_rotationMovement{rotationMovement}, m_lastMoveCall{}, m_movePeriod{movePeriod}
{

}

std::string MovableElement::getClassName() const
{
    return "MovableElement";
}

void MovableElement::move()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastMoveCall).count() >= m_movePeriod)
    {
        m_position.first += m_movement.first;
        m_position.second += m_movement.second;
        m_rotation += m_rotationMovement;
        m_lastMoveCall = std::chrono::system_clock::now();
    }
}

//Retourne la vitesse de l'objet par rapport à la vue en pixels/seconde
std::pair<float, float> MovableElement::getPixelSpeed() const
{
    return std::make_pair<float, float>((m_movement.first / m_movePeriod) * 1000, (m_movement.second / m_movePeriod) * 1000);
}

std::pair<float, float> MovableElement::getMovement() const
{
    return m_movement;
}

void MovableElement::setMovePeriod(float movePeriod)
{
    m_movePeriod = movePeriod;
}

void MovableElement::setMovement(float dx, float dy)
{
    m_movement.first = dx;
    m_movement.second = dy;
}
