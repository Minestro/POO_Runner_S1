#ifndef GAMECHARACTERGRAPHIC_H
#define GAMECHARACTERGRAPHIC_H

#include "spriteelement.h"
#include "circleshapeelement.h"

class GameCharacterGraphic: public SpriteElement
{
private:
    bool m_show;
public:
    GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Texture *texture, unsigned int animatePeriod = 0);
    GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, unsigned int activeLigne = 1, unsigned int activeColonne = 1, unsigned int animatePeriod = 0);
    virtual ~GameCharacterGraphic();
    void refresh(const Element *el, Model *model) override;
    void draw(sf::RenderTarget *window) const;
};

#endif // GAMECHARACTERGRAPHIC_H
