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

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "movableelement.h"

class Image: public MovableElement
{
private:
    bool m_isSliding;
    std::string  m_backgroundFileName;
    int m_zIndex;
    float m_coefSpeed;
public:
    Image(float x, float y, float width, float height, std::string backgroundFileName, int zIndex, float coefSpeed, bool isSliding = 0, int movePeriodMicroSec = 0);
    virtual ~Image() = default;
    std::string getBackgroundFileName() const;
    int getZIndex() const;
    float getCoefSpeed() const;
    bool isSliding() const;
    void move() override;
    std::string getClassName() const;
};

#endif // BACKGROUND_H
