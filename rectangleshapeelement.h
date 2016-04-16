#ifndef RECTANGLESHAPE_H
#define RECTANGLESHAPE_H

#include "graphicelement.h"

class RectangleShapeElement: public GraphicElement, public sf::RectangleShape
{
private:
    void rescale(float width, float height);
public:
    RectangleShapeElement() = default;
    RectangleShapeElement(unsigned int zIndex, float width, float height, float x, float y, sf::Color color = sf::Color::Black);
    virtual ~RectangleShapeElement() = default;
    virtual void setSize(float width, float height) override;
    virtual void setPosition(float x, float y) override;
    virtual std::pair<float, float> getSize() const override;
    virtual std::pair<float, float> getPosition() const override;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el);
};

#endif // RECTANGLESHAPE_H
