#include "graphicelement.h"
#include "iostream"

std::vector<sf::Texture*> GraphicElement::m_listTextures;

GraphicElement::GraphicElement(float width, float height, float x, float y, const sf::Texture &texture) : sf::Sprite::Sprite{}, m_size{width, height}
{
    setTexture(texture);
    setPosition(x, y);
}

void GraphicElement::rescale()
{
    sf::FloatRect bb = this->getLocalBounds();
    int width_factor = m_size.first / bb.width;
    int height_factor = m_size.second / bb.height;
    this->setScale(width_factor, height_factor);
}

void GraphicElement::setSize(float width, float height)
{
   m_size.first = width;
   m_size.second = height;
}


void GraphicElement::loadTextures(std::string themeName)
{
    std::vector<sf::Texture*>::iterator iterator = m_listTextures.begin();
    for (unsigned int i=0; i<sizeof(FILES_LIST)/sizeof(std::string); i++)
    {
        iterator = m_listTextures.insert(iterator, new sf::Texture);
        if (!((*iterator)->loadFromFile("Textures/" + themeName + "/" + FILES_LIST[i])))
        {
            std::cout << "Erreur lors du chargement de l'image" << "Textures/" << themeName << "/" << FILES_LIST[i];
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
