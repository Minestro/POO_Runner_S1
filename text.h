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

public:
    Text() = default;
    Text(float x, float y, float width, float height, std::string text, bool autoRescale = 1, bool wordBreak = 1);
    virtual ~Text() = default;
    void setText(std::string text);
    std::string getText() const;
    virtual std::string getClassName() const;
};

#endif // TEXT_H
