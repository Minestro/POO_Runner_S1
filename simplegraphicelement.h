#ifndef SIMPLEGRAPHICELEMENT_H
#define SIMPLEGRAPHICELEMENT_H

#include "graphicelement.h"

class SimpleGraphicElement: public GraphicElement
{
private:

public:
    SimpleGraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture);
    SimpleGraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, const sf::IntRect &textRect);
    void animate();
};

#endif // SIMPLEGRAPHICELEMENT_H
