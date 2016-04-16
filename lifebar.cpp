#include "lifebar.h"

LifeBar::LifeBar(unsigned int zIndex, float width, float height, float x, float y): GraphicElement::GraphicElement{zIndex}
{
    m_sprite = new SpriteElement{zIndex, width, height, x, y, GraphicElement::m_listTextures["life.png"]};
    m_bar = new RectangleShapeElement{zIndex, width, height, x, y};
}

LifeBar::~LifeBar()
{
    delete m_sprite;
    delete m_bar;
}


void LifeBar::setSize(float width, float height)
{
    m_sprite->setSize(width, height);
    m_bar->setSize(width, height);
}

void LifeBar::setPosition(float x, float y)
{
    m_sprite->setPosition(x, y);
    m_bar->setPosition(x, y);
}

std::pair<float, float> LifeBar::getSize() const
{
    return m_sprite->getSize();
}

std::pair<float, float> LifeBar::getPosition() const
{
    return m_sprite->getPosition();
}

std::string LifeBar::getClassName() const
{
    return "LifeBar";
}

void LifeBar::draw(sf::RenderWindow *window) const
{
    m_bar->draw(window);
    m_sprite->draw(window);
}

void LifeBar::refresh(const Element *el)
{
    const GameCharacter *gc = dynamic_cast<const GameCharacter*>(el);
    m_bar->setSize(m_sprite->getSize().first * ((float)gc->getLife() / (float)MAX_LIFE), m_bar->getSize().second);
}
