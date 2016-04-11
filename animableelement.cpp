#include "animableelement.h"
#include <iostream>

AnimableElement::AnimableElement(unsigned int zIndex, int nbLignes, int nbColonnes, float width, float height, float x, float y, const sf::Texture *texture,  int animatePeriod, int activeLigne, int activeColonne)
    : GraphicElement::GraphicElement{zIndex, width, height, x, y, texture, nbLignes, nbColonnes, activeLigne, activeColonne}, m_animatePeriod{animatePeriod}
{
    refreshTextRect();
}

void AnimableElement::animate()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastAnimateCall).count() > m_animatePeriod)
    {
        if( (m_activeColonne%m_nbColonnes) > 0 )
        {
            setRectPos(m_activeLigne, m_activeColonne+1);
        }
        else
        {
            setRectPos(m_activeLigne, 1);
        }
        m_lastAnimateCall = std::chrono::system_clock::now();
    }
}

std::string AnimableElement::getClassName() const
{
    return "AnimableElement";
}

void AnimableElement::setAnimatePeriod(float a)
{
    m_animatePeriod = a;
}
