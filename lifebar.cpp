#include "lifebar.h"
#include "model.h"

LifeBar::LifeBar(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, unsigned int refreshPeriod): GraphicElement::GraphicElement{zIndex, refreshPeriod}, m_actualBarWidth{(unsigned int)width}, m_ratioLife{1.0f}
{
    m_sprite = new SpriteElement{zIndex, width, height, x, y, rotateAngle, GraphicElement::m_listTextures["life.png"]};
    m_bar = new RectangleShapeElement{zIndex, width, height, x, y, rotateAngle, sf::Color::Green};
    setPosition(x, y);
}

LifeBar::~LifeBar()
{
    delete m_sprite;
    delete m_bar;
}


void LifeBar::setSize(float width, float height)
{
    m_sprite->setSize(width, height);
    m_bar->setSize(width * m_ratioLife, height);
    setPosition(m_sprite->getPosition().first, m_sprite->getPosition().second);
}

void LifeBar::setPosition(float x, float y)
{
    m_sprite->setPosition(x, y);
    m_bar->setPosition(x, y);
}

void LifeBar::setRotation(float angle)
{
    m_sprite->setRotation(angle);
    m_bar->setRotation(angle);
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

#include <iostream>
void LifeBar::refresh(const Element *el, Model *model)
{
    std::vector<std::pair<bool, GameCharacter*> >::const_iterator it = model->getCharacters().begin();
    while (it != model->getCharacters().end() && it->second != el)
    {
        ++it;
    }
    if (it != model->getCharacters().end())
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastRefeshCall).count() >= m_refreshPeriod)
        {
            HSLColor beginColor = color2hsl(0, 255, 0);
            HSLColor endColor = color2hsl(255, 0, 0);
            sf::Color finalColor;
            m_ratioLife = (float)it->second->getLife() / (float)MAX_LIFE;
            if (m_actualBarWidth > m_sprite->getSize().first * m_ratioLife + 1)
            {
                m_actualBarWidth--;
            } else if (m_actualBarWidth < m_sprite->getSize().first * m_ratioLife - 1)
            {
                m_actualBarWidth++;
            }
            if (std::abs(m_actualBarWidth - (m_sprite->getSize().first * m_ratioLife)) > 100)
            {
                m_actualBarWidth = m_sprite->getSize().first * m_ratioLife;
            }
            m_bar->setSize(m_actualBarWidth, m_sprite->getSize().second);
            m_bar->setPosition(m_sprite->getPosition().first, m_sprite->getPosition().second);
            float deltaColorDeg = beginColor.h - endColor.h;
            float h =  beginColor.h - deltaColorDeg * (1.0 - (m_actualBarWidth / m_sprite->getSize().first));
            if (h >= 360)
            {
                h -= 360;
            } else if (h < 0)
            {
                h += 360;
            }
            finalColor = hsl2color(h, beginColor.s, beginColor.l);
            m_bar->setFillColor(finalColor);
            m_lastRefeshCall = std::chrono::system_clock::now();
        }
        if (it->second->getId() > character_id::PLAYER1)
        {
            setPosition(el->getPosition().first, el->getPosition().second - 15);
            setSize(el->getSize().first, 10.0);
        }
    }
}
