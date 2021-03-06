/*Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

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
        for (const std::pair <bool, std::chrono::time_point<std::chrono::system_clock> > &power : model->getApp()->getGameModel().getActivesPowers())
        {
            if (power.first)
            {
                powerText += Player::getStringPower(i, model->getApp()->getSettings().m_lang);
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
        case character_state::ALIVE:
            if (model->getApp()->getGameModel().getActivesPowers()[power_list::INVINCIBILITY].first && getActiveColonne() == 1)
            {
                setRectPos(2, 1);
            } else if (!model->getApp()->getGameModel().getActivesPowers()[power_list::INVINCIBILITY].first && getActiveColonne() == 2)
            {
                setRectPos(1, 1);
            }
            break;
        default:
            break;
        }
    }
    animate();
}
