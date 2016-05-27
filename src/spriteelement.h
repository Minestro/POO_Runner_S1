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

#ifndef SPRITEELEMENT_H
#define SPRITEELEMENT_H

#include "graphicelement.h"

class SpriteElement: public GraphicElement, public sf::Sprite
{
protected:
    unsigned int m_nbLignes;            //Le nb de ligne c'est à dire le nb d'images par ligne
    unsigned int m_nbColonnes;          //Le nb d'images par colonnes
    unsigned int m_activeLigne;
    unsigned int m_activeColonne;
    std::chrono::time_point<std::chrono::system_clock> m_lastAnimateCall;
    unsigned int m_animatePeriod;
    bool m_autoLoop;                        //Le rectangle de lecture revient au début une fois qu'il a atteint la fin de la colonne
    bool m_animationDirectionRight;         //Le rectangle de lecture se déplace de gauche à droite = true ou de droite à gauche = false
    void rescale(float width, float height);
public:
    SpriteElement(unsigned int zIndex, const sf::Texture *texture, unsigned int animatePeriod = 0);
    SpriteElement(unsigned int zIndex, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, unsigned int activeLigne = 1, unsigned int activeColonne = 1, bool autoLoop = 1, unsigned int animatePeriod = 0, bool animationDirectionright = 1);
    virtual ~SpriteElement() = default;
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const override;
    int getNbLignes() const;
    int getActiveColonne() const;
    virtual std::string getClassName() const;
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    void setRectPos(int ligne, int colonne=1);
    void setAutoLoop(bool autoLoop);
    void setNbLignes(unsigned int nb);
    void setNbColonnes(unsigned int nb);
    void setAnimatePeriod(unsigned int a);
    virtual void animate();
    void refreshTextRect();
    void changeDirectionSprite(bool directionRight);
    virtual void draw(sf::RenderTarget *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // SPRITEELEMENT_H
