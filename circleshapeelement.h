#ifndef CIRCLESHAPEELEMENT_H
#define CIRCLESHAPEELEMENT_H

#include "graphicelement.h"

class CircleShapeElement: public GraphicElement, public sf::CircleShape
{
private:
    void rescale(float width, float height);
public:
    CircleShapeElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Color color = sf::Color::Black);
    virtual ~CircleShapeElement() = default;
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const override;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // CIRCLESHAPEELEMENT_H
