#include "textelement.h"
#include <iostream>

std::map<std::string, sf::Font*> TextElement::m_listFonts;

TextElement::TextElement(unsigned int zIndex, float width, float height, float x, float y, std::string text, const sf::Font *font, unsigned int fontSize, bool autoRescale, bool wordBreak, sf::Color color, int style, text_effect effect, unsigned int refreshPeriod): GraphicElement::GraphicElement{zIndex, refreshPeriod}, sf::Text{text, *font, fontSize}, m_realPosition{x, y}, m_realSize{width, height}, m_autoRescale{autoRescale}, m_wordBreak{wordBreak}, m_textLines{}, m_effect{effect}, m_breath{1}, m_textForm{}, m_alphaChannel{0}
{
    if (m_wordBreak)
    {
        m_autoRescale = 0;
    }
    setStyle(style);
    setSize(width, height);
    setColor(color);
    setText(text);
}

void TextElement::setText(std::string text)
{
    if (m_wordBreak)
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
            if (lineGraphic.getLocalBounds().width > m_realSize.first)
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
    }
}

void TextElement::rescale(float width, float height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = width / bb.width;
    float height_factor = height / bb.height;
    setScale(width_factor, height_factor);
}

void TextElement::setSize(float width, float height)
{
    m_realSize.first = width;
    m_realSize.second = height;
    if (m_wordBreak)
    {
        std::string text = "";
        for (unsigned int i = 0; i<m_textLines.size(); i++)
        {
            text += m_textLines[i] + " ";
        }
        setText(text);
    }
    if ((getLocalBounds().width > m_realSize.first || getLocalBounds().height > m_realSize.second) && m_autoRescale)
    {
        rescale(m_realSize.first, m_realSize.second);
    }
    setPosition(m_realPosition.first, m_realPosition.second);
}

void TextElement::setPosition(float x, float y)
{
    m_realPosition.first = x;
    m_realPosition.second = y;
    if (m_autoRescale)
    {
        sf::Text::setPosition(((m_realSize.first-(getLocalBounds().width*getScale().x))/2)+m_realPosition.first, ((m_realSize.second-(getLocalBounds().height*getScale().y))/2)+ m_realPosition.second);
    } else {
        sf::Text::setPosition(x, y);
    }
}

std::pair<float, float> TextElement::getSize() const
{
    if (m_autoRescale)
    {
        return m_realSize;
    } else {
        if (!m_wordBreak)
        {
            return {Text::getLocalBounds().width, Text::getLocalBounds().height};
        } else {
            return {m_realSize.first, Text::getLocalBounds().height * m_textLines.size()};
        }
    }
}

std::pair<float, float> TextElement::getPosition() const
{
    return m_realPosition;

}

std::string TextElement::getClassName() const
{
    return "TextElement";
}

void TextElement::generateTextForm()
{
    sf::Text line {"", *getFont(), getCharacterSize()};
    line.setColor(sf::Color::White);
    line.setStyle(getStyle());
    m_textForm.create(GAME_SIZE_W, GAME_SIZE_H);
    m_textForm.setSmooth(1);
    m_textForm.clear(sf::Color::Transparent);
    for (unsigned int i = 0; i<m_textLines.size(); i++)
    {
        line.setString(m_textLines[i]);
        line.setPosition(0, i * getLocalBounds().height);
        m_textForm.draw(line);
    }
    m_textForm.display();
}

void TextElement::draw(sf::RenderWindow *window) const
{
    if (m_wordBreak)
    {
        sf::Sprite textS{m_textForm.getTexture()};
        textS.setPosition(m_realPosition.first, m_realPosition.second);
        textS.setColor(sf::Color{getColor().r, getColor().g, getColor().b, (sf::Uint8)m_alphaChannel});
        window->draw(textS);
    } else {
        window->draw(*this);
    }
}

void TextElement::refresh(const Element *el, Model *model)
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

void TextElement::loadFonts(std::string themeName)
{
    m_listFonts.clear();
    std::map<std::string, sf::Font*>::iterator iterator = m_listFonts.begin();
    for (unsigned int i=0; i<sizeof(FONTS_LIST)/sizeof(*FONTS_LIST); i++)
    {
        iterator = m_listFonts.insert(iterator, std::make_pair(FONTS_LIST[i], new sf::Font));
        if (!(iterator->second->loadFromFile("Ressources/" + themeName + "/Fonts/" + FONTS_LIST[i])))
        {
            std::cout << "Erreur lors du chargement de la police" << "Ressources/" << themeName << "/Fonts/" << FONTS_LIST[i] << std::endl;
        }
    }
}

void TextElement::clearFonts()
{
    std::map<std::string, sf::Font*>::iterator iterator = m_listFonts.begin();
    while (iterator != m_listFonts.end())
    {
        delete iterator->second;
        ++iterator;
    }
    m_listFonts.clear();
}
