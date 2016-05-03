#include "buttongraphic.h"

ButtonGraphic::ButtonGraphic(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, std::string text, const sf::Font *font, unsigned int fontSize, sf::Color color, int style, unsigned int refreshPeriod): GraphicElement::GraphicElement{zIndex, refreshPeriod}, m_size{width, height}, m_position{x, y}
{
    m_text = new TextElement{zIndex, width, height, x, y, rotateAngle, text, font, fontSize, 1, 0, color, style};
    m_sprite = new SpriteElement{zIndex, width, height, x, y, rotateAngle, GraphicElement::m_listTextures["buttons.png"], 1, 2, 1, 1, 0};
}

ButtonGraphic::~ButtonGraphic()
{
    delete m_text;
    delete m_sprite;
}

void ButtonGraphic::setSize(float width, float height)
{
    m_size.first = width;
    m_size.second = height;
    m_text->setSize(width, height);
    m_sprite->setSize(width, height);
}

void ButtonGraphic::setPosition(float x, float y)
{
    m_position.first = x;
    m_position.second = y;
    m_text->setPosition(x, y);
    m_sprite->setPosition(x, y);
}

void ButtonGraphic::setRotation(float angle)
{
    m_text->setRotation(angle);
    m_sprite->setRotation(angle);
}

std::pair<float, float> ButtonGraphic::getSize() const
{
    return m_size;
}

std::pair<float, float> ButtonGraphic::getPosition() const
{
    return m_position;
}

std::string ButtonGraphic::getClassName() const
{
    return "ButtonGraphic";
}

void ButtonGraphic::draw(sf::RenderWindow *window) const
{
    m_sprite->draw(window);
    m_text->draw(window);
}

void ButtonGraphic::refresh(const Element *el, Model *model)
{
    std::vector<std::pair<bool, Button*> >::const_iterator button = model->getButtons().begin();
    while (button != model->getButtons().end() && button->second != el)
    {
        ++button;
    }
    if (button != model->getButtons().end())
    {
        m_text->setString(button->second->getText());
        m_text->refresh(el, model);
        m_size = el->getSize();
        m_sprite->setSize(m_size.first, m_size.second);
        m_position = el->getPosition();
        m_sprite->setPosition(m_position.first, m_position.second);
        setRotation(el->getRotateAngle());
        if (button->second->isHover(model->getCursorPosition().first, model->getCursorPosition().second))
        {
            m_sprite->setRectPos(1, 2);
        } else {
            m_sprite->setRectPos(1, 1);
        }
    }
}
