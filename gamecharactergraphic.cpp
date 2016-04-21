#include "gamecharactergraphic.h"
#include <iostream>

GameCharacterGraphic::GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, int animatePeriod, int nbLignes, int nbColonnes, int activeLigne, int activeColonne): SpriteElement::SpriteElement{zIndex, width, height, x, y, texture, animatePeriod, nbLignes, nbColonnes, activeLigne, activeColonne}
{

}

void GameCharacterGraphic::refresh(const Element *el, Model *model)
{
    setPosition(el->getPosition().first, el->getPosition().second);
    setSize(el->getSize().first, el->getSize().second);
    std::vector<GameCharacter*>::const_iterator it = model->getCharacters().begin();
    while (it != model->getCharacters().end() && *it != el)
    {
        ++it;
    }
    if (it != model->getCharacters().end())
    {
        float vitesseBalle = model->getCharacterSpeed(*it).first;
        if (vitesseBalle >= 0)
        {
            changeDirectionSprite(1);
        } else {
            changeDirectionSprite(0);
        }
        float perimetreBalle = PI * (**it).getSize().first;
        setAnimatePeriod(std::abs((1/(vitesseBalle/perimetreBalle))/getNbLignes())*500);
    }
    animate();
}
