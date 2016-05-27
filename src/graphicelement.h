#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <chrono>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
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

#include "const.h"

class Element;
class Model;

enum Shaders_effects{BLUR_EFFECT, PIXELATE_EFFECT};

struct HSLColor
{
    float h;
    float s;
    float l;
};

class GraphicElement
{
protected:
    GraphicElement(unsigned int zIndex, unsigned int refreshPeriod = 0);
    unsigned int m_zIndex;          //A quel "couche" doit on afficher l'objet lors du rendu de  l'image
    std::chrono::time_point<std::chrono::system_clock> m_lastRefeshCall;
    unsigned int m_refreshPeriod;
public:
    virtual ~GraphicElement() = default;
    virtual void setSize(float width, float height) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual std::pair<float, float> getSize() const = 0;
    virtual std::pair<float, float> getPosition() const = 0;
    unsigned int getZIndex() const;
    virtual std::string getClassName() const = 0;
    bool operator<(const GraphicElement &ge) const;
    virtual void refresh(const Element *el, Model *model)=0;
    virtual void draw(sf::RenderTarget *window) const=0;

    static std::map<std::string, sf::Texture*> m_listTextures;
    static void loadTextures(std::string themeName="Default");
    static void clearTextures();
    static std::map<int, sf::Shader*> m_listShaders;
    static void loadShaders();
    static void clearShaders();
    static sf::Color hsl2color(float h, float s, float l);
    static HSLColor color2hsl(int r, int g, int b);
};


#endif // GRAPHICELEMENT_H
