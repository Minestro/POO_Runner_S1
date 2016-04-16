#include "textelement.h"
#include <iostream>

std::map<std::string, sf::Font*> TextElement::m_listFonts;

TextElement::TextElement(unsigned int zIndex, float width, float height, float x, float y, std::string text, const sf::Font *font, unsigned int fontSize, sf::Color color, int style): GraphicElement::GraphicElement{zIndex}, sf::Text{text, *font, fontSize}, m_realPosition{x, y}, m_realSize{width, height}
{
    setOrigin(0, 0);
    setStyle(style);
    setSize(width, height);
    setColor(color);
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
    if (getLocalBounds().width > m_realSize.first || getLocalBounds().height > m_realSize.second)
    {
        rescale(m_realSize.first, m_realSize.second);
    } else {
        setScale(1 ,1);
    }
    setPosition(m_realPosition.first, m_realPosition.second);
}

void TextElement::setPosition(float x, float y)
{
    m_realPosition.first = x;
    m_realPosition.second = y;
    sf::Text::setPosition(((m_realSize.first-(getLocalBounds().width*getScale().x))/2)+m_realPosition.first, ((m_realSize.second-(getLocalBounds().height*getScale().y))/2)+ m_realPosition.second);
}

std::pair<float, float> TextElement::getSize() const
{
    return m_realSize;
}

std::pair<float, float> TextElement::getPosition() const
{
    return m_realPosition;

}

std::string TextElement::getClassName() const
{
    return "TextElement";
}

void TextElement::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}

void TextElement::refresh(const Element *el)
{
    setSize(el->getSize().first, el->getSize().second);
    setPosition(el->getPosition().first, el->getPosition().second);
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
