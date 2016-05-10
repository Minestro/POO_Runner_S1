#ifndef TEXT_H
#define TEXT_H

#include "element.h"

class Text: public Element
{
private:
    bool m_lineBreak;
    bool m_autoRescale;
    std::string m_text;
    unsigned int m_fontSize;
    ColorRGBA m_color;
    std::string m_font;
    text_effect m_effect;
    unsigned int m_effectPeriod;

public:
    Text() = default;
    Text(float x, float y, float width, float height, float rotation, std::string text, unsigned int fontSize, std::string font, bool autoRescale = 1, bool lineBreak = 1);
    Text(float x, float y, float width, float height, float rotation, std::string text, unsigned int fontSize, std::string font, ColorRGBA color = ColorRGBA::Black, text_effect effect = text_effect::NOTHING, unsigned int effectPeriod = 0, bool autoRescale = 1, bool lineBreak = 1);
    virtual ~Text() = default;
    void setText(std::string text);
    std::string getText() const;
    unsigned int getFontSize() const;
    ColorRGBA getColor() const;
    std::string getFont() const;
    text_effect getEffect() const;
    unsigned int getEffectPeriod() const;
    bool getlineBreak() const;
    bool getAutoRescale() const;
    virtual std::string getClassName() const;
};

#endif // TEXT_H
