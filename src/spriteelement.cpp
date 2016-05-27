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

#include "spriteelement.h"
#include "model.h"

SpriteElement::SpriteElement(unsigned int zIndex, const sf::Texture *texture, unsigned int animatePeriod): GraphicElement::GraphicElement{zIndex}, sf::Sprite::Sprite{}, m_nbLignes{1}, m_nbColonnes{1}, m_activeLigne{1}, m_activeColonne{1}, m_lastAnimateCall{}, m_animatePeriod{animatePeriod}, m_autoLoop{1}, m_animationDirectionRight{1}
{
    setTexture(*texture);
    refreshTextRect();

}

SpriteElement::SpriteElement(unsigned int zIndex, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, unsigned int activeLigne, unsigned int activeColonne, bool autoLoop, unsigned int animatePeriod, bool animationDirectionright): GraphicElement::GraphicElement{zIndex}, sf::Sprite::Sprite{}, m_nbLignes{nbLignes}, m_nbColonnes{nbColonnes}, m_activeLigne{activeLigne}, m_activeColonne{activeColonne}, m_lastAnimateCall{}, m_animatePeriod{animatePeriod}, m_autoLoop{autoLoop}, m_animationDirectionRight{animationDirectionright}
{
    setTexture(*texture);
    refreshTextRect();
}

void SpriteElement::rescale(float width, float height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float height_factor = height / bb.height;
    float width_factor;
    if (getTexture()->isRepeated())
    {
        width_factor = (width / bb.width) * 2;
    } else {
        width_factor = width / bb.width;
    }
    setScale(width_factor, height_factor);
}

int SpriteElement::getNbLignes() const
{
    return m_nbLignes;
}

int SpriteElement::getActiveColonne() const
{
    return m_activeColonne;
}

std::string SpriteElement::getClassName() const
{
    return "SpriteElement";
}

std::pair<float, float> SpriteElement::getPosition() const
{
    return {sf::Sprite::getPosition().x - getOrigin().x * getScale().x, sf::Sprite::getPosition().y - getOrigin().y * getScale().y};
}

std::pair<float, float> SpriteElement::getSize() const
{
    return {getGlobalBounds().width, getGlobalBounds().height};
}

void SpriteElement::setSize(float width, float height)
{
    rescale(width, height);
    setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
}

void SpriteElement::setPosition(float x, float y)
{
    sf::Sprite::setPosition(x + getOrigin().x * getScale().x, y + getOrigin().y * getScale().y);
}

void SpriteElement::setRectPos(int ligne, int colonne)
{
    if (ligne < (int)m_nbLignes + 1 && ligne > 0 && colonne < (int)m_nbColonnes + 1 && colonne > 0)
    {
        m_activeColonne = colonne;
        m_activeLigne = ligne;
        if (m_nbLignes > 1 || m_nbColonnes > 1)
        {
            refreshTextRect();
        }
    }
}

void SpriteElement::setAutoLoop(bool autoLoop)
{
    m_autoLoop = autoLoop;
}

void SpriteElement::setNbColonnes(unsigned int nb)
{
    m_nbColonnes = nb;
}

void SpriteElement::setNbLignes(unsigned int nb)
{
    m_nbLignes = nb;
}

void SpriteElement::changeDirectionSprite(bool directionRight)
{
    m_animationDirectionRight = directionRight;
}

void SpriteElement::animate()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastAnimateCall).count() >= m_animatePeriod)
    {
        if (m_animationDirectionRight)
        {
            if ((m_activeColonne%m_nbColonnes) > 0 )
            {
                setRectPos(m_activeLigne, ++m_activeColonne);
            }
            else if (m_autoLoop)
            {
                setRectPos(m_activeLigne, 1);
            }
        } else {
            if (m_activeColonne > 1)
            {
                setRectPos(m_activeLigne, --m_activeColonne);
            }
            else if (m_autoLoop)
            {
                setRectPos(m_activeLigne, m_nbColonnes);
            }
        }
        m_lastAnimateCall = std::chrono::system_clock::now();
    }
}

void SpriteElement::setAnimatePeriod(unsigned int a)
{
    m_animatePeriod = a;
}

void SpriteElement::refreshTextRect()
{
    setTextureRect(sf::IntRect{
                       (int)((m_activeColonne-1) * (getTexture()->getSize().x / m_nbColonnes)),
                       (int)((m_activeLigne-1) * (getTexture()->getSize().y / m_nbLignes)),
                       (int)(getTexture()->getSize().x / m_nbColonnes),
                       (int)(getTexture()->getSize().y / m_nbLignes)});
}

void SpriteElement::draw(sf::RenderTarget *window) const
{
    window->draw(*this);
}

void SpriteElement::refresh(const Element *el, Model *model)
{
    (void) model;
    setSize(el->getSize().first, el->getSize().second);
    setPosition(el->getPosition().first, el->getPosition().second);
    setRotation(el->getRotateAngle());

    if (el->getClassName() == "Obstacle")
    {
        std::vector<std::pair<bool, Obstacle*> >::iterator obstacle = model->getObstacles().begin();
        while (obstacle != model->getObstacles().end() && obstacle->second != el)
        {
            ++obstacle;
        }
        if (obstacle != model->getObstacles().end())
        {
            switch (obstacle->second->getState())
            {
            case obstacle_state::EXPLODE:
                if (getTexture() != GraphicElement::m_listTextures["explosion.png"])
                {
                    setTexture(* GraphicElement::m_listTextures["explosion.png"]);
                    setNbLignes(1);
                    setNbColonnes(81);
                    setRectPos(1);
                    setAnimatePeriod(10);
                }
                setAutoLoop(0);
                if (m_activeColonne == m_nbColonnes)
                {
                    model->getDeletedElements().push_back(el);
                    model->getObstacles().erase(obstacle);
                }
                break;
            default:
                break;
            }
        }
    }

    animate();
}

