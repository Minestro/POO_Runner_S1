#ifndef ANIMABLEELEMENT_H
#define ANIMABLEELEMENT_H
#include "graphicelement.h"

class AnimableElement: public GraphicElement
{
private:
    int m_nbLignes;
    int m_nbColonnes;
    int m_activeLigne;
    int m_activeColonne;
    std::pair<int, int> m_rectSpriteSize;
public:
    AnimableElement() = default;
    AnimableElement(unsigned int zIndex, int nbLignes, int nbColonnes, int widthRect, int heightRect, float width, float height, float x, float y, const sf::Texture *texture);
    void animate();
    void setRectPos(int ligne, int colonne);
};

#endif // ANIMABLEELEMENT_H
