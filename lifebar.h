#ifndef LIFEBAR_H
#define LIFEBAR_H

#include <SFML/Graphics.hpp>
#include "rectangleshapeelement.h"
#include "spriteelement.h"
#include "gamecharacter.h"

class LifeBar: public GraphicElement
{
private:
    SpriteElement *m_sprite;
    RectangleShapeElement *m_bar;
    unsigned int m_actualBarWidth;
    float m_ratioLife;
public:
    LifeBar(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, unsigned int refreshPeriod = 0);
    virtual ~LifeBar();
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y);
    void setRotation(float angle);
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // LIFEBAR_H
