#include "animableelement.h"

AnimableElement::AnimableElement(unsigned int zIndex, int nbLignes, int nbColonnes, float width, float height, float x, float y, const sf::Texture *texture)
    : GraphicElement::GraphicElement{zIndex, width, height, x, y, texture}, m_nbLignes{nbLignes}, m_nbColonnes{nbColonnes}, m_activeLigne{1}, m_activeColonne{1}
{
    setTextureRect(sf::IntRect{0, 0, texture->getSize().x / m_nbLignes, texture->getSize().y / m_nbColonnes});
}
void AnimableElement::animate()
{

    if( (m_activeColonne%m_nbColonnes) <0 )
    {
        m_activeColonne++;
    }
    else
        m_activeColonne=1;
}

void AnimableElement::setRectPos(int ligne, int colonne)
{
    m_activeColonne= colonne;
    m_activeLigne = ligne;

}
