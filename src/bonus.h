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

#ifndef BONUS_H
#define BONUS_H

#include "movableelement.h"

enum bonus_type{COIN, INVINSIBLE, MAGNET, MEDIC, SLOW_TIME_BONUS};

class Bonus: public MovableElement
{
private:
    int m_type;    //Le type de bonus
public:
    Bonus(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod, int type);
    virtual ~Bonus() = default;
    std::string getClassName() const;
    int getType() const;
};

#endif // BONUS_H

