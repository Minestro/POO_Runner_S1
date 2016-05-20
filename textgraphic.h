#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "graphicelement.h"
#include "const.h"

class TextElement: public GraphicElement, public sf::Text
{
private:
    void rescale(float width, float height);
    std::pair<float, float> m_realPosition;
    std::pair<float, float> m_realSize;
    bool m_autoRescale;
    bool m_lineBreak;
    std::vector<std::string> m_textLines;
    int m_effect;
    bool m_breath;
    sf::RenderTexture m_textForm;
    int m_alphaChannel;

    void generateTextForm();
public:
    TextElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, std::string text, const sf::Font *font, unsigned int fontSize, bool autoRescale = 1, bool lineBreak = 1, sf::Color color = sf::Color::Black, int style = 0, int effect = text_effect::NOTHING, unsigned int refreshPeriod = 0);
    virtual ~TextElement() = default;
    void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    void setText(std::string text);
    virtual std::pair<float, float> getSize() const;
    virtual std::string getClassName() const;
    virtual std::pair<float, float> getPosition() const override;
    virtual void draw(sf::RenderTarget *window) const;
    virtual void refresh(const Element *el, Model *model);

    static std::map<std::string, sf::Font*> m_listFonts;
    static void loadFonts(std::string themeName="Default");
    static void clearFonts();
};

#endif // TEXTELEMENT_H
