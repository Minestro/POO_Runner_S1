#ifndef CONVEXSHAPE_H
#define CONVEXSHAPE_H

#include "graphicelement.h"

class ConvexShapeElement: public GraphicElement, public sf::ConvexShape
{
private:

public:
    ConvexShapeElement() = default;
    ConvexShapeElement(unsigned int zIndex, float width, float height, float x, float y, float nbPoints, sf::Color color = sf::Color::Black);
    virtual ~ConvexShapeElement() = default;
    void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const override;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el);
};

#endif // CONVEXSHAPE_H
