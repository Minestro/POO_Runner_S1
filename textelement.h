#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "graphicelement.h"

enum text_effect{NOTHING, BREATH, FLASH};

class TextElement: public GraphicElement, public sf::Text
{
private:
    void rescale(float width, float height);
    std::pair<float, float> m_realPosition;
    std::pair<float, float> m_realSize;
    bool m_autoRescale;
    bool m_wordBreak;
    std::vector<std::string> m_textLines;
    text_effect m_effect;
    bool m_breath;

public:
    TextElement() = default;
    TextElement(unsigned int zIndex, float width, float height, float x, float y, std::string text, const sf::Font *font, unsigned int fontSize, bool autoRescale = 1, bool wordBreak = 1, sf::Color color = sf::Color::Black, int style = 0, text_effect effect = text_effect::NOTHING, unsigned int refreshPeriod = 0);
    virtual ~TextElement() = default;
    void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    void setText(std::string text);
    virtual std::pair<float, float> getSize() const;
    virtual std::string getClassName() const;
    virtual std::pair<float, float> getPosition() const override;
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el, Model *model);

    static std::map<std::string, sf::Font*> m_listFonts;
    static void loadFonts(std::string themeName="Default");
    static void clearFonts();
};

#endif // TEXTELEMENT_H
