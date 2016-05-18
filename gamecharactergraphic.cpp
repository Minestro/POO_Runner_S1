#include "gamecharactergraphic.h"
#include "model.h"

GameCharacterGraphic::GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Texture *texture, unsigned int animatePeriod): SpriteElement::SpriteElement{zIndex, width, height, x, y, rotateAngle, texture, animatePeriod}
{
}

GameCharacterGraphic::GameCharacterGraphic(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, unsigned int activeLigne, unsigned int activeColonne, unsigned int animatePeriod): SpriteElement::SpriteElement{zIndex, width, height, x, y, rotateAngle, texture, nbLignes, nbColonnes, activeLigne, activeColonne, 1, animatePeriod}
{
}

GameCharacterGraphic::~GameCharacterGraphic()
{
}

void GameCharacterGraphic::draw(sf::RenderTarget *window) const
{
    SpriteElement::draw(window);
}

void GameCharacterGraphic::refresh(const Element *el, Model *model)
{
    setPosition(el->getPosition().first, el->getPosition().second);
    setSize(el->getSize().first, el->getSize().second);
    setRotation(el->getRotateAngle());
    std::vector<std::pair<bool, GameCharacter*> >::iterator it = model->getCharacters().begin();
    while (it != model->getCharacters().end() && it->second != el)
    {
        ++it;
    }
    if (it != model->getCharacters().end())
    {
        switch (it->second->getState())
        {
        case character_state::DYING:
            if (getTexture() != GraphicElement::m_listTextures["explosion.png"])
            {
                setTexture(* GraphicElement::m_listTextures["explosion.png"]);
                setNbLignes(1);
                setNbColonnes(81);
                setRectPos(1);
                setAutoLoop(0);
            }
            if (m_activeColonne == m_nbColonnes)
            {
                model->getDeletedElements().push_back(el);
                model->getCharacters().erase(it);
            }
            break;
        default:

            break;
        }
    }
    animate();
}
