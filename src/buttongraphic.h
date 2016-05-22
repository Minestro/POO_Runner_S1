#ifndef BUTTONGRAPHIC_H
#define BUTTONGRAPHIC_H

#include "textgraphic.h"
#include "spriteelement.h"

class ButtonGraphic: public GraphicElement
{
private:
    std::pair<float, float> m_size;
    std::pair<float, float> m_position;
    TextGraphic *m_text;
    SpriteElement *m_sprite;
public:
    ButtonGraphic(unsigned int zIndex, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, std::string text, const sf::Font *font, unsigned int fontSize, const sf::Color color, int style = 0, unsigned int refreshPeriod = 0);
    virtual ~ButtonGraphic();
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y);
    void setRotation(float angle);
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderTarget *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // BUTTONGRAPHIC_H
