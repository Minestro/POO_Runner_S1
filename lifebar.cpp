#include "lifebar.h"

LifeBar::LifeBar(unsigned int zIndex, float width, float height, float x, float y): GraphicElement::GraphicElement{zIndex}
{
    m_sprite = new SpriteElement{zIndex, width, height, x, y, GraphicElement::m_listTextures["life.png"]};
    m_bar = new RectangleShapeElement{zIndex, width-6, height-6, x+3, y+3};
}

LifeBar::~LifeBar()
{
    delete m_sprite;
    delete m_bar;
}


void LifeBar::setSize(float width, float height)
{
    m_sprite->setSize(width, height);
    m_bar->setSize(width-6, height-6);
}

void LifeBar::setPosition(float x, float y)
{
    m_sprite->setPosition(x, y);
    m_bar->setPosition(x+3, y+3);
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

void LifeBar::refresh(const Element *el, Model *model)
{
    std::vector<GameCharacter*>::const_iterator it = model->getCharacters().begin();
    while (it != model->getCharacters().end() && *it != el)
    {
        ++it;
    }
    if (it != model->getCharacters().end())
    {
        m_bar->setSize(m_sprite->getSize().first * ((float)(**it).getLife() / (float)MAX_LIFE)-6, m_sprite->getSize().second-6);
    }
}
