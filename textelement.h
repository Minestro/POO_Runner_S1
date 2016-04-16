#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "graphicelement.h"

class TextElement: public GraphicElement, public sf::Text
{
private:
    void rescale(float width, float height);
    std::pair<float, float> m_realPosition;
    std::pair<float, float> m_realSize;
public:
    TextElement() = default;
    TextElement(unsigned int zIndex, float width, float height, float x, float y, std::string text, const sf::Font *font, unsigned int fonSize, sf::Color color = sf::Color::Black, int style = 0);
    virtual ~TextElement() = default;
    void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    virtual std::pair<float, float> getSize() const;
    virtual std::string getClassName() const;
    virtual std::pair<float, float> getPosition() const override;
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el);

    static std::map<std::string, sf::Font*> m_listFonts;
    static void loadFonts(std::string themeName="Default");
    static void clearFonts();
};

#endif // TEXTELEMENT_H
