#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <chrono>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
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
    unsigned int m_zIndex;
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