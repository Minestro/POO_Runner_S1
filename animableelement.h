#ifndef ANIMABLEELEMENT_H
#define ANIMABLEELEMENT_H
#include "graphicelement.h"
#include <SFML/System/Clock.hpp>

class AnimableElement: public GraphicElement
{
private:
    int m_nbLignes;
    int m_nbColonnes;
    int m_activeLigne;
    int m_activeColonne;
    std::pair<int, int> m_rectSpriteSize;
    sf::Clock m_clock;
    int m_animatePeriod;
public:
    AnimableElement() = default;
    AnimableElement(unsigned int zIndex, int nbLignes, int nbColonnes, float width, float height, float x, float y, const sf::Texture *texture, int animatePeriod, int activeLigne = 1, int activeColonne = 1);
    void animate();
    void setRectPos(int ligne, int colonne);
    void setAnimatePeriod();
};

#endif // ANIMABLEELEMENT_H
