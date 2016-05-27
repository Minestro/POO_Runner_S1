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

#include "image.h"

Image::Image(float x, float y, float width, float height, std::string backgroundFileName, int zIndex, float coefSpeed, bool isSliding, int movePeriodMicroSec):MovableElement{x, y, width, height, 0, -PIXELPERBACKGROUNDMOVE, 0, 0, movePeriodMicroSec}, m_isSliding{isSliding}, m_backgroundFileName{backgroundFileName}, m_zIndex{zIndex}, m_coefSpeed{coefSpeed}
{

}

std::string Image::getClassName() const
{
    return "Background";
}

std::string Image::getBackgroundFileName() const
{
    return m_backgroundFileName;
}

void Image::move()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastMoveCall).count() > m_movePeriod && m_isSliding)
    {
        if (m_position.first - (m_movement.first * m_coefSpeed) > -m_size.first)
        {
            m_position.first += m_movement.first * m_coefSpeed;
        } else {
            m_position.first = 0;
        }
        m_lastMoveCall = std::chrono::system_clock::now();
    }
}

int Image::getZIndex() const
{
    return m_zIndex;
}

bool Image::isSliding() const
{
    return m_isSliding;
}

float Image::getCoefSpeed() const
{
    return m_coefSpeed;
}
