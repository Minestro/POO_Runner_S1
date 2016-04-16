#include "graphicelement.h"
#include <iostream>

std::map<std::string, sf::Texture*> GraphicElement::m_listTextures;

GraphicElement::GraphicElement(unsigned int zIndex):m_zIndex{zIndex}
{

}

unsigned int GraphicElement::getZIndex() const
{
    return m_zIndex;
}

bool GraphicElement::operator<(const GraphicElement &ge) const
{
    return(this->m_zIndex < ge.m_zIndex);
}

void GraphicElement::loadTextures(std::string themeName)
{
    m_listTextures.clear();
    std::map<std::string, sf::Texture*>::iterator iterator = m_listTextures.begin();
    for (unsigned int i=0; i<sizeof(FILES_LIST)/sizeof(*FILES_LIST); i++)
    {
        iterator = m_listTextures.insert(iterator, std::make_pair(FILES_LIST[i], new sf::Texture));
        if (!(iterator->second->loadFromFile("Ressources/" + themeName + "/Textures/" + FILES_LIST[i])))
        {
            std::cout << "Erreur lors du chargement de l'image" << "Ressources/" << themeName << "/Textures/" << FILES_LIST[i] << std::endl;
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

