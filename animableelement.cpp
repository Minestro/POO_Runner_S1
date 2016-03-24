#include "animableelement.h"

AnimableElement::AnimableElement(unsigned int zIndex, int nbLignes, int nbColonnes, int widthRect, int heightRect, float width, float height, float x, float y, const sf::Texture *texture): GraphicElement::GraphicElement{zIndex, width, height, x, y, texture, sf::IntRect{0, 0, m_rectSpriteSize.first, m_rectSpriteSize.second}}, m_nbLignes{nbLignes}, m_nbColonnes{nbColonnes}, m_rectSpriteSize{widthRect, heightRect}
{

}
