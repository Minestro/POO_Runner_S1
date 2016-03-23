#include "animableelement.h"

AnimableElement::AnimableElement(int nbLignes, int nbColonnes, int widthRect, int heightRect, float width, float height, float x, float y, const sf::Texture &texture): GraphicElement::GraphicElement{width, height, x, y, texture}, m_nbLignes{nbLignes}, m_nbColonnes{nbColonnes}, m_rectSpriteSize{widthRect, heightRect}
{

}
