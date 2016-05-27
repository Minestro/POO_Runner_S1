#ifndef ELEMENT_H
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

#define ELEMENT_H

#include <vector>
#include <string>
#include <math.h>
#include "const.h"

#define IDNOTSET 0

enum pointsName{UL, UR, DL, DR};

struct ColorRGBA
{
    ColorRGBA();
    ColorRGBA(unsigned int cr, unsigned int cg, unsigned int cb, unsigned int alpha = 255);
    unsigned int r, g, b, a;
    static const ColorRGBA White;
    static const ColorRGBA Black;
    static const ColorRGBA Red;
};

class Element
{
protected:
    Element(float x, float y, float w, float h, float rotation, unsigned long int id = 0);
    unsigned long int m_id;             //L'id de l'élément n'est pas obligatoire. Si il n'est pas définit il reste à 0
    std::pair <float, float> m_position; //first : x, second : y
    std::pair <float, float> m_size;  //first : w, second : h
    float m_rotation;
public:
    virtual ~Element() = default;
    virtual std::string getClassName() const=0;
    std::pair<float, float> getSize() const;
    std::pair<float, float> getPosition() const;
    float getRotateAngle() const;
    unsigned int getId() const;
    std::vector<std::pair<float, float> > getPointsAfterRotation() const;
    void setSize(float w, float h);
    void setPosition(float x, float y);
    void setId(unsigned long int id);
    bool collision(const Element *el) const;
    virtual std::pair<float, float> getPixelSpeed() const;
};

#endif // ELEMENT_H
