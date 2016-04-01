#include "graphicelement.h"
#include <iostream>

std::map<std::string, sf::Texture*> GraphicElement::m_listTextures;

GraphicElement::GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture) : sf::Sprite::Sprite{}, m_size{width, height}, m_zIndex{zIndex}
{
    setTexture(*texture);
    setPosition(x, y);
    rescale();
}

GraphicElement::GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, const sf::IntRect &textRect) : sf::Sprite::Sprite{}, m_size{width, height}, m_zIndex{zIndex}
{
    setTexture(*texture);
    setTextureRect(textRect);
    setPosition(x, y);
    rescale();
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
    std::map<std::string, sf::Texture*>::iterator iterator = m_listTextures.begin();
    for (unsigned int i=0; i<sizeof(FILES_LIST)/sizeof(*FILES_LIST); i++)
    {
        iterator = m_listTextures.insert(iterator, std::make_pair(FILES_LIST[i], new sf::Texture));
        if (!(iterator->second->loadFromFile("Textures/" + themeName + "/" + FILES_LIST[i])))
        {
            std::cout << "Erreur lors du chargement de l'image" << "Textures/" << themeName << "/" << FILES_LIST[i] << std::endl;
        } else {
            iterator->second->setSmooth(true);
        }
    }
}

void GraphicElement::clearTextures()
{
    std::map<std::string, sf::Texture*>::iterator iterator = m_listTextures.begin();
    while (iterator != m_listTextures.end())
    {
        delete iterator->second;
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


void GraphicElement::rescale()
{
    sf::FloatRect bb = this->getLocalBounds();
    float height_factor = m_size.second / bb.height;
    float width_factor;
    if (getTexture()->isRepeated())                         //on considére que seul les sliding backgrounds ont leurs textures en repeated
    {
        width_factor = (m_size.first / bb.width) *2;
    } else {
        width_factor = m_size.first / bb.width;
    }
    this->setScale(width_factor, height_factor);
}


bool GraphicElement::operator==(const GraphicElement &ge) const
{
    return (this->getTexture() == ge.getTexture() && this->getSize() == ge.getSize() && this->getPosition() == ge.getPosition() && this->getTexture()->isRepeated() == ge.getTexture()->isRepeated() && this->m_zIndex == ge.m_zIndex);
}

bool GraphicElement::operator<(const GraphicElement &ge) const
{
    return(this->m_zIndex < ge.m_zIndex);
}

