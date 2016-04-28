#ifndef GAMECHARACTERGRAPHIC_H
#define GAMECHARACTERGRAPHIC_H

#include "spriteelement.h"
#include "circleshapeelement.h"

class GameCharacterGraphic: public SpriteElement
{
private:
    CircleShapeElement *m_shadow;
public:
    GameCharacterGraphic() = default;
    GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, int animatePeriod = 0);
    GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, int nbLignes, int nbColonnes, int activeLigne = 1, int activeColonne = 1, int animatePeriod = 0);
    virtual ~GameCharacterGraphic();
    void refresh(const Element *el, Model *model) override;
    void draw(sf::RenderWindow *window) const;
};

#endif // GAMECHARACTERGRAPHIC_H
