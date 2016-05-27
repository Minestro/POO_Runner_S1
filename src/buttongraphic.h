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

#ifndef BUTTONGRAPHIC_H
#define BUTTONGRAPHIC_H

#include "textgraphic.h"
#include "spriteelement.h"

class ButtonGraphic: public GraphicElement
{
private:
    std::pair<float, float> m_size;
    std::pair<float, float> m_position;
    TextGraphic *m_text;
    SpriteElement *m_sprite;
public:
    ButtonGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, std::string text, const sf::Font *font, unsigned int fontSize, const sf::Color color, int style = 0, unsigned int refreshPeriod = 0);
    virtual ~ButtonGraphic();
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y);
    void setRotation(float angle);
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderTarget *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // BUTTONGRAPHIC_H
