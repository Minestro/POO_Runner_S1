#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <SFML/Graphics.hpp>
#include <list>
#include "const.h"

class GraphicElement: public sf::Sprite
{
protected:
    std::pair<float, float> m_size;
    unsigned int m_zIndex;
public:
    GraphicElement() = default;
    GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture);
    GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, const sf::IntRect &textRect);
    virtual ~GraphicElement();
    void rescale();
    void setSize(float width, float height);
    std::pair<float, float> getSize() const;
    unsigned int getZIndex() const;
    virtual std::string getClassName() const=0;
    bool operator==(const GraphicElement &ge) const;
    bool operator<(const GraphicElement &ge) const;
    virtual void animate()=0;

    static std::map<std::string, sf::Texture*> m_listTextures;
    static void loadTextures(std::string themeName="Default");
    static void clearTextures();
};


#endif // GRAPHICELEMENT_H
