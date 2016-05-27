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

#include "buttongraphic.h"
#include "model.h"
#include "app.h"

ButtonGraphic::ButtonGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, std::string text, const sf::Font *font, unsigned int fontSize, const sf::Color color, int style, unsigned int refreshPeriod): GraphicElement::GraphicElement{zIndex, refreshPeriod}, m_size{}, m_position{}
{
    m_text = new TextGraphic{zIndex, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, text, font, fontSize, 1, 0, color, style};
    m_sprite = new SpriteElement{zIndex, texture, nbLignes, nbColonnes, 1, 1, 0};
}

ButtonGraphic::~ButtonGraphic()
{
    delete m_text;
    delete m_sprite;
}

void ButtonGraphic::setSize(float width, float height)
{
    m_size.first = width;
    m_size.second = height;
    m_text->setSize(width, height);
    m_sprite->setSize(width, height);
}

void ButtonGraphic::setPosition(float x, float y)
{
    m_position.first = x;
    m_position.second = y;
    m_text->setPosition(x, y);
    m_sprite->setPosition(x, y);
}

void ButtonGraphic::setRotation(float angle)
{
    m_text->setRotation(angle);
    m_sprite->setRotation(angle);
}

std::pair<float, float> ButtonGraphic::getSize() const
{
    return m_size;
}

std::pair<float, float> ButtonGraphic::getPosition() const
{
    return m_position;
}

std::string ButtonGraphic::getClassName() const
{
    return "ButtonGraphic";
}

void ButtonGraphic::draw(sf::RenderTarget *window) const
{
    m_sprite->draw(window);
    m_text->draw(window);
}

void ButtonGraphic::refresh(const Element *el, Model *model)
{
    std::vector<std::pair<bool, Button*> >::const_iterator button = model->getButtons().begin();
    while (button != model->getButtons().end() && button->second != el)
    {
        ++button;
    }
    if (button != model->getButtons().end())
    {
        setSize(el->getSize().first, el->getSize().second);
        setPosition(el->getPosition().first, el->getPosition().second);
        setRotation(el->getRotateAngle());

        switch (button->second->getType())
        {
        case button_type::TEXT_BUTTON:
            m_text->setString(button->second->getText());
            m_text->refresh(el, model);
            if (button->second->isHover(model->getCursorPosition().first, model->getCursorPosition().second) && button->second->isClickable())
            {
                if (m_sprite->getActiveColonne() == 1)
                {
                    model->getApp()->getSound().playSound("click.wav");
                }
                m_sprite->setRectPos(1, 2);
            } else if (!button->second->isClickable()) {
                m_sprite->setRectPos(1, 3);
            } else {
                m_sprite->setRectPos(1, 1);
            }
            break;
        case button_type::RADIO_BUTTON:
            m_text->setString("");
            m_text->refresh(el, model);
            if (button->second-> isOn())
            {
                m_sprite->setRectPos(1, 1);
            } else {
                m_sprite->setRectPos(1, 2);
            }
            break;
        case button_type::SAVE_BUTTON:
            if (button->second->isHover(model->getCursorPosition().first, model->getCursorPosition().second) && button->second->isClickable())
            {
                if (m_sprite->getActiveColonne() == 1)
                {
                    model->getApp()->getSound().playSound("click.wav");
                }
                m_sprite->setRectPos(1, 2);
            } else {
                m_sprite->setRectPos(1, 1);
            }
            if (button->second->isSelected())
            {
                m_sprite->setRectPos(1, 3);
            }
            break;
        default:
            break;
        }
    }
}
