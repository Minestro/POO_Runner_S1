#include "gamecharactergraphic.h"
#include "model.h"
#include "app.h"

GameCharacterGraphic::GameCharacterGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int animatePeriod): SpriteElement::SpriteElement{zIndex, texture, animatePeriod}, m_powerActiveText{zIndex, 0.0f, 0.0f, 250.0f, 600.0f, 0.0f, "", TextGraphic::m_listFonts["score.ttf"], 20, 0, 0, sf::Color::White}, m_show{1}
{
}

GameCharacterGraphic::GameCharacterGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, unsigned int activeLigne, unsigned int activeColonne, unsigned int animatePeriod): SpriteElement::SpriteElement{zIndex, texture, nbLignes, nbColonnes, activeLigne, activeColonne, 1, animatePeriod}, m_powerActiveText{zIndex, 0.0f, 0.0f, 250.0f, 600.0f, 0.0f, "", TextGraphic::m_listFonts["score.ttf"], 20, 0, 0, sf::Color::White}, m_show{1}
{
}

GameCharacterGraphic::~GameCharacterGraphic()
{
}

void GameCharacterGraphic::draw(sf::RenderTarget *window) const
{
    if (m_show)
    {
        SpriteElement::draw(window);
        m_powerActiveText.draw(window);
    }
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
        std::string powerText = "";
        unsigned int i = 0;
        for (std::pair <bool, std::chrono::time_point<std::chrono::system_clock> > power : model->getApp()->getGameModel().getActivesPowers())
        {
            if (power.first)
            {
                powerText = Player::getStringPower(i);
                powerText += " : " + std::to_string(-std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-power.second).count()) + " s   ";
            }
            i++;
        }
        m_powerActiveText.setText(powerText);
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
                setAnimatePeriod(20);
            }
            if (m_activeColonne == m_nbColonnes)
            {
                it->second->setState(character_state::DEAD);
                m_show = false;
            }
            break;
        default:
            break;
        }
    }
    animate();
}
