#include "graphicelement.h"
#include <iostream>

std::vector<sf::Texture*> GraphicElement::m_listTextures;

GraphicElement::GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture) : sf::Sprite::Sprite{}, m_size{width, height}, m_zIndex{zIndex}
{
    setTexture(*texture);
    setPosition(x, y);
    //rescale();
}

GraphicElement::GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, const sf::IntRect &textRect) : sf::Sprite::Sprite{}, m_size{width, height}, m_zIndex{zIndex}
{
    setTexture(*texture);
    setTextureRect(textRect);
    setPosition(x, y);
    //rescale();
}

void GraphicElement::rescale()
{
    sf::FloatRect bb = this->getLocalBounds();
    int height_factor = m_size.second / bb.height;
    int width_factor;
    if (this->getTexture()->isRepeated())
    {
        width_factor = (m_size.first / bb.width)/2;
    } else {
        width_factor = m_size.first / bb.width;
    }
    this->setScale(width_factor, height_factor);
}

void GraphicElement::setSize(float width, float height)
{
   m_size.first = width;
   m_size.second = height;
   rescale();
}


void GraphicElement::loadTextures(std::string themeName)
{
    m_listTextures.clear();
    std::vector<sf::Texture*>::iterator iterator = m_listTextures.begin();
    for (unsigned int i=0; i<2; i++)
    {
        iterator = m_listTextures.insert(iterator, new sf::Texture);
        if (!((*iterator)->loadFromFile("Textures/" + themeName + "/" + FILES_LIST[i])))
        {
            std::cout << "Erreur lors du chargement de l'image" << "Textures/" << themeName << "/" << FILES_LIST[i];
        } else {
            (*iterator)->setSmooth(true);
        }
    }
}

void GraphicElement::clearTextures()
{
    std::vector<sf::Texture*>::iterator iterator = m_listTextures.begin();
    while (iterator != m_listTextures.end())
    {
        delete *iterator;
        ++iterator;
    }
    m_listTextures.clear();
}

std::pair<float, float> GraphicElement::getSize() const
{
    return m_size;
}

unsigned int GraphicElement::getZIndex() const
{
    return m_zIndex;
}

bool GraphicElement::operator==(const GraphicElement &ge) const
{
    return (this->getTexture() == ge.getTexture() && this->getSize() == ge.getSize() && this->getPosition() == ge.getPosition() && this->getTexture()->isRepeated() == ge.getTexture()->isRepeated() && this->m_zIndex == ge.m_zIndex);
}
bool GraphicElement::operator<(const GraphicElement &ge) const
{
    return(this->m_zIndex < ge.m_zIndex);
}
