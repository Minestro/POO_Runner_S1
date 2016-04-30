#include "text.h"

Text::Text(float x, float y, float width, float height, std::string text, unsigned int fontSize, std::string font, bool autoRescale, bool wordBreak): Element{x, y, width, height}, m_wordBreak{wordBreak}, m_autoRescale{autoRescale}, m_text{text}, m_fontSize{fontSize}, m_r{255}, m_g{255}, m_b{255}, m_font{font}, m_effect{text_effect::NOTHING}, m_effectPeriod{0}
{

}

Text::Text(float x, float y, float width, float height, std::string text, unsigned int fontSize, std::string font, unsigned int r, unsigned int g, unsigned int b, text_effect effect, unsigned int effectPeriod, bool autoRescale, bool wordBreak): Element{x, y, width, height}, m_wordBreak{wordBreak}, m_autoRescale{autoRescale}, m_text{text}, m_fontSize{fontSize}, m_r{r}, m_g{g}, m_b{b}, m_font{font}, m_effect{effect}, m_effectPeriod{effectPeriod}
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

unsigned int Text::getR() const
{
    return m_r;
}

unsigned int Text::getG() const
{
    return m_g;
}

unsigned int Text::getB() const
{
    return m_b;
}

std::string Text::getFont() const
{
    return m_font;
}

text_effect Text::getEffect() const
{
    return m_effect;
}

bool Text::getAutoRescale() const
{
    return m_autoRescale;
}

bool Text::getWordBreak() const
{
    return m_wordBreak;
}

unsigned int Text::getEffectPeriod() const
{
    return m_effectPeriod;
}
