#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <list>
#include <SFML/Graphics.hpp>
#include "const.h"
#include "model.h"

class GraphicElement
{
protected:
    unsigned int m_zIndex;
public:
    GraphicElement() = default;
    GraphicElement(unsigned int zIndex);
    virtual ~GraphicElement() = default;
    virtual void setSize(float width, float height) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual std::pair<float, float> getSize() const = 0;
    virtual std::pair<float, float> getPosition() const = 0;
    unsigned int getZIndex() const;
    virtual std::string getClassName() const = 0;
    bool operator<(const GraphicElement &ge) const;
    virtual void refresh(const Element *el, Model *model)=0;
    virtual void draw(sf::RenderWindow *window) const=0;

    static std::map<std::string, sf::Texture*> m_listTextures;
    static void loadTextures(std::string themeName="Default");
    static void clearTextures();
};


#endif // GRAPHICELEMENT_H
