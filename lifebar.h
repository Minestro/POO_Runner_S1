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
public:
    LifeBar() = default;
    LifeBar(unsigned int zIndex, float width, float height, float x, float y);
    virtual ~LifeBar();
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y);
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const override;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // LIFEBAR_H
