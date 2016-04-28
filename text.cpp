#include "text.h"

Text::Text(float x, float y, float width, float height, std::string text, bool autoRescale, bool wordBreak): Element::Element{x, y, width, height}, m_wordBreak{wordBreak}, m_autoRescale{autoRescale}, m_textLines{}, m_text{text}
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
