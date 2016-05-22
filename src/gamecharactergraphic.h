#ifndef GAMECHARACTERGRAPHIC_H
#define GAMECHARACTERGRAPHIC_H

#include <chrono>
#include "spriteelement.h"
#include "textgraphic.h"

class GameCharacterGraphic: public SpriteElement
{
private:
    TextGraphic m_powerActiveText;
    bool m_show;

public:
    GameCharacterGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int animatePeriod = 0);
    GameCharacterGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, unsigned int activeLigne = 1, unsigned int activeColonne = 1, unsigned int animatePeriod = 0);
    virtual ~GameCharacterGraphic();
    void refresh(const Element *el, Model *model) override;
    void draw(sf::RenderTarget *window) const;
};

#endif // GAMECHARACTERGRAPHIC_H
