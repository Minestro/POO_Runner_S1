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

#include "textgraphic.h"
#include "model.h"
#include <iostream>

std::map<std::string, sf::Font*> TextGraphic::m_listFonts;

TextGraphic::TextGraphic(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, std::string text, const sf::Font *font, unsigned int fontSize, bool autoRescale, bool lineBreak, sf::Color color, int style, int effect, unsigned int refreshPeriod): GraphicElement::GraphicElement{zIndex, refreshPeriod}, sf::Text{text, *font, fontSize}, m_realPosition{x, y}, m_realSize{width, height}, m_autoRescale{autoRescale}, m_lineBreak{lineBreak}, m_textLines{}, m_effect{effect}, m_breath{1}, m_textForm{}, m_alphaChannel{255}
{
    if (m_lineBreak)
    {
        m_autoRescale = 0;
    }
    setStyle(style);
    setSize(width, height);
    setColor(color);
    setText(text);
    setRotation(rotateAngle);
}

void TextGraphic::setText(std::string text)
{
    if (m_lineBreak)        //Algorithme qui arrange le texte si le retour à la ligne est activé
    {
        m_textLines.clear();
        int i = 0;
        int l = 0;
        int wordCount = 0;
        std::string word;
        m_textLines.push_back("");
        sf::Text lineGraphic{m_textLines[l], *getFont(), getCharacterSize()};
        while (i < (int)text.size())
        {
            if (lineGraphic.getLocalBounds().width <= m_realSize.first)
            {
                word = "";
                while (text[i] != ' ' && i < (int)text.size())
                {
                    word.push_back(text[i]);
                    i++;
                }
                i++;
            }
            wordCount++;
            lineGraphic.setString(m_textLines[l] + word);
            if (lineGraphic.getLocalBounds().width > m_realSize.first || word == "\n")
            {
                if (wordCount == 1)
                {
                    m_textLines[l] += word + " ";
                }
                m_textLines.push_back("");
                l++;
                wordCount = 0;
            } else {
                if (wordCount > 1)
                {
                    m_textLines[l] += " ";
                }
                m_textLines[l] += word;
            }
        }
        generateTextForm();
    } else {
        setString(text);
        setSize(getSize().first, getSize().second);
    }
}

void TextGraphic::rescale(float width, float height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = width / bb.width;
    float height_factor = height / bb.height;
    setScale(width_factor, height_factor);
}

void TextGraphic::setSize(float width, float height)
{
    m_realSize.first = width;
    m_realSize.second = height;
    if (m_lineBreak)
    {
        std::string text = "";
        for (unsigned int i = 0; i<m_textLines.size(); i++)
        {
            text += m_textLines[i] + " ";
        }
        setText(text);
    }
    if ((getLocalBounds().width > m_realSize.first || getLocalBounds().height > m_realSize.second) && m_autoRescale && m_realSize.first != 0.0f && m_realSize.second != 0.0f)
    {
        rescale(m_realSize.first, m_realSize.second);
    }
    setPosition(m_realPosition.first, m_realPosition.second);
}

void TextGraphic::setPosition(float x, float y)
{
    m_realPosition.first = x;
    m_realPosition.second = y;
    if (m_autoRescale)
    {
        sf::Text::setPosition(((m_realSize.first-(getLocalBounds().width*getScale().x))/2)+m_realPosition.first, (m_realSize.second/2)-(getLocalBounds().height*getScale().y/2) + m_realPosition.second - 5);
    } else {
        sf::Text::setPosition(x, y);
    }
}

std::pair<float, float> TextGraphic::getSize() const
{
    if (m_autoRescale)
    {
        return m_realSize;
    } else {
        if (!m_lineBreak)
        {
            return {Text::getLocalBounds().width, Text::getLocalBounds().height};
        } else {
            return {m_realSize.first, Text::getLocalBounds().height * m_textLines.size()};
        }
    }
}

std::pair<float, float> TextGraphic::getPosition() const
{
    return m_realPosition;

}

std::string TextGraphic::getClassName() const
{
    return "TextElement";
}

std::string TextGraphic::getText() const
{
    if (m_lineBreak)
    {
        std::string text = "";
        for (unsigned int i = 0; i<m_textLines.size(); i++)
        {
            text += m_textLines[i] + " ";
        }
        return text;
    } else {
        return sf::Text::getString();
    }
}

void TextGraphic::generateTextForm()
{
    float r = getRotation();
    setRotation(0);
    sf::Text line {"", *getFont(), getCharacterSize()};
    line.setColor(sf::Color::White);
    line.setStyle(getStyle());
    m_textForm.create(MODEL_SIZE_W, MODEL_SIZE_H);
    m_textForm.setSmooth(1);
    m_textForm.clear(sf::Color::Transparent);
    for (unsigned int i = 0; i<m_textLines.size(); i++)
    {
        line.setString(m_textLines[i]);
        line.setPosition(0, i * getLocalBounds().height);
        m_textForm.draw(line);
    }
    setRotation(r);
    m_textForm.display();
}

void TextGraphic::draw(sf::RenderTarget *window) const
{
    if (m_lineBreak)
    {
        sf::Sprite textS{m_textForm.getTexture()};
        textS.setOrigin(textS.getLocalBounds().width / 2, textS.getLocalBounds().height / 2);
        textS.setPosition(m_realPosition.first + textS.getOrigin().x, m_realPosition.second + textS.getOrigin().y);
        textS.setColor(sf::Color{getColor().r, getColor().g, getColor().b, (sf::Uint8)m_alphaChannel});
        textS.setRotation(getRotation());
        window->draw(textS);
    } else {
        window->draw(*this);
    }
}

void TextGraphic::refresh(const Element *el, Model *model)
{
    (void) model;
    if (m_realPosition != el->getPosition())
    {
        setPosition(el->getPosition().first, el->getPosition().second);
    }
    if (m_realSize != el->getSize())
    {
        setSize(el->getSize().first, el->getSize().second);
    }
    setRotation(el->getRotateAngle());

    std::vector<std::pair<bool, runner::Text*> >::iterator text = model->getTexts().begin();
    while (text != model->getTexts().end() && text->second != el)
    {
        ++text;
    }
    if (text != model->getTexts().end())
    {
        if (getText() != text->second->getText())
        {
            setText(text->second->getText());
        }
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastRefeshCall).count() >= m_refreshPeriod)
    {
        switch (m_effect)
        {
        case text_effect::BREATH:
            if (m_breath)
            {
                if (m_alphaChannel + 10 <= 255)
                {
                    m_alphaChannel += 10;
                    setColor(sf::Color{getColor().r, getColor().g, getColor().b, (sf::Uint8)m_alphaChannel});
                } else {
                    m_breath = !m_breath;
                }
            } else {
                if (m_alphaChannel -10 >= 0)
                {
                    m_alphaChannel -= 10;
                    setColor(sf::Color{getColor().r, getColor().g, getColor().b, (sf::Uint8)m_alphaChannel});
                } else {
                    m_breath = !m_breath;
                }
            }
            break;
        case text_effect::FLASH:
            m_alphaChannel = std::abs(255 - m_alphaChannel);
            setColor(sf::Color{getColor().r, getColor().g, getColor().b, (sf::Uint8)m_alphaChannel});
            break;
        default:
            break;
        }
        m_lastRefeshCall = std::chrono::system_clock::now();
    }
}

void TextGraphic::loadFonts(std::string themeName)
{
    m_listFonts.clear();
    std::map<std::string, sf::Font*>::iterator iterator = m_listFonts.begin();
    for (unsigned int i=0; i<sizeof(FONTS_LIST)/sizeof(*FONTS_LIST); i++)
    {
        iterator = m_listFonts.insert(iterator, std::make_pair(FONTS_LIST[i], new sf::Font));
        if (!(iterator->second->loadFromFile("Ressources/" + themeName + "/Fonts/" + FONTS_LIST[i])))
        {

        }
    }
}

void TextGraphic::clearFonts()
{
    std::map<std::string, sf::Font*>::iterator iterator = m_listFonts.begin();
    while (iterator != m_listFonts.end())
    {
        delete iterator->second;
        ++iterator;
    }
    m_listFonts.clear();
}
