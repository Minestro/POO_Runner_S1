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

#ifndef GAMECHARACTERGRAPHIC_H
#define GAMECHARACTERGRAPHIC_H

#include <chrono>
#include "spriteelement.h"
#include "textgraphic.h"

class GameCharacterGraphic: public SpriteElement
{
private:
    TextGraphic m_powerActiveText;
    bool m_show;

public:
    GameCharacterGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int animatePeriod = 0);
    GameCharacterGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, unsigned int activeLigne = 1, unsigned int activeColonne = 1, unsigned int animatePeriod = 0);
    virtual ~GameCharacterGraphic();
    void refresh(const Element *el, Model *model) override;
    void draw(sf::RenderTarget *window) const;
};

#endif // GAMECHARACTERGRAPHIC_H
