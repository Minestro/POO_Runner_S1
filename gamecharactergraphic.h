#ifndef GAMECHARACTERGRAPHIC_H
#define GAMECHARACTERGRAPHIC_H

#include "spriteelement.h"

class GameCharacterGraphic: public SpriteElement
{
public:
    GameCharacterGraphic() = default;
    GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, int animatePeriod = 0, int nbLignes = 1, int nbColonnes = 1, int activeLigne = 1, int activeColonne = 1);
    virtual ~GameCharacterGraphic() = default;
    void refresh(const Element *el, Model *model) override;
};

#endif // GAMECHARACTERGRAPHIC_H
