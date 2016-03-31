#include "animableelement.h"
#include <iostream>

AnimableElement::AnimableElement(unsigned int zIndex, int nbLignes, int nbColonnes, float width, float height, float x, float y, const sf::Texture *texture,  int animatePeriod, int activeLigne, int activeColonne)
    : GraphicElement::GraphicElement{zIndex, width, height, x, y, texture, sf::IntRect{(int)((activeColonne-1) * (texture->getSize().x / nbColonnes)), (int) ((activeLigne-1) * (texture->getSize().y / nbLignes)), (int)texture->getSize().x / nbColonnes, (int)texture->getSize().y / nbLignes}}, m_nbLignes{nbLignes}, m_nbColonnes{nbColonnes}, m_activeLigne{activeLigne}, m_activeColonne{activeColonne}, m_clock{}, m_animatePeriod{animatePeriod}
{

}
void AnimableElement::animate()
{
    if (m_clock.getElapsedTime().asMilliseconds() > m_animatePeriod)
    {
        if( (m_activeColonne%m_nbColonnes) > 0 )
        {
            m_activeColonne++;
        }
        else
        {
            m_activeColonne=1;
        }
        setTextureRect(sf::IntRect{(int)((m_activeColonne-1) * (getTexture()->getSize().x / m_nbColonnes)), (int) ((m_activeLigne-1) * (getTexture()->getSize().y / m_nbLignes)), (int)getTexture()->getSize().x / m_nbColonnes, (int)getTexture()->getSize().y / m_nbLignes});
        m_clock.restart();
    }
}

void AnimableElement::setRectPos(int ligne, int colonne)
{
    m_activeColonne= colonne;
    m_activeLigne = ligne;

}

std::string AnimableElement::getClassName() const
{
    return "AnimableElement";
}
