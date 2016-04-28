#include "graphicelement.h"
#include <iostream>

std::map<std::string, sf::Texture*> GraphicElement::m_listTextures;

GraphicElement::GraphicElement(unsigned int zIndex, int refreshPeriod):m_zIndex{zIndex}, m_lastRefeshCall{}, m_refreshPeriod{refreshPeriod}
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

float HueToRGB(float v1, float v2, float vH) {
    if (vH < 0)
    {
        vH += 1;
    }
    if (vH > 1)
    {
        vH -= 1;
    }
    if ((6 * vH) < 1)
    {
        return (v1 + (v2 - v1) * 6 * vH);
    }
    if ((2 * vH) < 1)
    {
        return v2;
    }
    if ((3 * vH) < 2)
    {
        return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);
    }
    return v1;
}

sf::Color GraphicElement::hsl2color(float h, float s, float l) {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    if (s == 0)
    {
        r = g = b = (unsigned char)(l * 255);
    }
    else
    {
        float v1, v2;
        float hue = (float)h / 360;

        if (l < 0.5)
        {
            v2 = l * (1 + s);
        } else {
            v2 = (l + s) - (l * s);
        }
        v1 = 2 * l - v2;

        r = (unsigned char)(255 * HueToRGB(v1, v2, hue + (1.0f / 3)));
        g = (unsigned char)(255 * HueToRGB(v1, v2, hue));
        b = (unsigned char)(255 * HueToRGB(v1, v2, hue - (1.0f / 3)));
    }

    return {(sf::Uint8)r, (sf::Uint8)g, (sf::Uint8)b};
}

HSLColor GraphicElement::color2hsl(int r, int g, int b)
{
    float h;
    float s;
    float l;
    if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
    {
        h = 0; s = 0; l = 0;
    } else {
        float r2 = (float)r/255.0f;
        float g2 = (float)g/255.0f;
        float b2 = (float)b/255.0f;
        float cMax = std::max(std::max(r2, g2), b2);
        float cMin = std::min(std::max(r2, g2), b2);
        float delta = cMax - cMin;
        if (delta == 0)
        {
            h = 0;
        } else if (cMax == r2)
        {
            h = 60 * ((int)((g2 - b2)/delta)%6);
        } else if (cMax == g2)
        {
            h = 60 * (((b2 - r2)/delta) + 2);
        } else {
            h = 60 * (((r2 - g2)/delta) + 4);
        }
        l = (cMax + cMin) / 2;
        if (delta == 0)
        {
            s = 0;
        } else {
            s = delta / (1 - std::abs(2*l - 1));
        }
    }
    HSLColor color;
    color.h = h; color.l = l; color.s = s;
    return color;
}
