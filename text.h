#ifndef TEXT_H
#define TEXT_H

#include "element.h"

class Text: public Element
{
private:
    bool m_wordBreak;
    bool m_autoRescale;
    std::string m_text;
    unsigned int m_fontSize;
    unsigned int m_r, m_g, m_b;
    std::string m_font;
    text_effect m_effect;
    unsigned int m_effectPeriod;

public:
    Text() = default;
    Text(float x, float y, float width, float height, std::string text, unsigned int fontSize, std::string font, bool autoRescale = 1, bool wordBreak = 1);
    Text(float x, float y, float width, float height, std::string text, unsigned int fontSize, std::string font, unsigned int r = 255, unsigned int g = 255, unsigned int b = 255, text_effect effect = text_effect::NOTHING, unsigned int effectPeriod = 0, bool autoRescale = 1, bool wordBreak = 1);
    virtual ~Text() = default;
    void setText(std::string text);
    std::string getText() const;
    unsigned int getFontSize() const;
    unsigned int getR() const;
    unsigned int getG() const;
    unsigned int getB() const;
    std::string getFont() const;
    text_effect getEffect() const;
    unsigned int getEffectPeriod() const;
    bool getWordBreak() const;
    bool getAutoRescale() const;
    virtual std::string getClassName() const;
};

#endif // TEXT_H
