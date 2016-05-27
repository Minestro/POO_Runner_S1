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

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "movableelement.h"

enum obstacle_type{MINE,NUAGE,BARRE};
enum obstacle_state{ACTIVE, EXPLODE};

class Obstacle: public MovableElement
{
private:
    unsigned int m_dammage; //Le nombre de points de vie qu'enlève l'obstacle.
    int m_state;
    int m_type;
public:
    Obstacle(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod,unsigned int dammage, int type);
    virtual ~Obstacle() = default;
    void setState(int state);
    unsigned int getDammage() const;
    std::string getClassName() const;
    int getState() const;
    int getType() const;
};

#endif // OBSTACLE_H
