#ifndef SIMPLEGRAPHICELEMENT_H
#define SIMPLEGRAPHICELEMENT_H

#include "graphicelement.h"

class SimpleGraphicElement: public GraphicElement
{
private:

public:
    SimpleGraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture);
    SimpleGraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, const sf::IntRect &textRect);
    virtual ~SimpleGraphicElement();
    std::string getClassName() const;
    void animate() override;
};

#endif // SIMPLEGRAPHICELEMENT_H
