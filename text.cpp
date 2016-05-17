#include "text.h"

Text::Text(float x, float y, float width, float height, float rotation, std::string text, unsigned int fontSize, std::string font, bool autoRescale, bool lineBreak): Element{x, y, width, height, rotation}, m_lineBreak{lineBreak}, m_autoRescale{autoRescale}, m_text{text}, m_fontSize{fontSize}, m_color{ColorRGBA::White}, m_font{font}, m_effect{text_effect::NOTHING}, m_effectPeriod{0}
{

}

Text::Text(float x, float y, float width, float height, float rotation, std::string text, unsigned int fontSize, std::string font, ColorRGBA color, int effect, unsigned int effectPeriod, bool autoRescale, bool lineBreak): Element{x, y, width, height, rotation}, m_lineBreak{lineBreak}, m_autoRescale{autoRescale}, m_text{text}, m_fontSize{fontSize}, m_color{color}, m_font{font}, m_effect{effect}, m_effectPeriod{effectPeriod}
{

}

void Text::setText(std::string text)
{
    m_text = text;
}

std::string Text::getText() const
{
    return m_text;
}

std::string Text::getClassName() const
{
    return "Text";
}

unsigned int Text::getFontSize() const
{
    return m_fontSize;
}

ColorRGBA Text::getColor() const
{
    return m_color;
}

std::string Text::getFont() const
{
    return m_font;
}

int Text::getEffect() const
{
    return m_effect;
}

bool Text::getAutoRescale() const
{
    return m_autoRescale;
}

bool Text::getlineBreak() const
{
    return m_lineBreak;
}

unsigned int Text::getEffectPeriod() const
{
    return m_effectPeriod;
}
