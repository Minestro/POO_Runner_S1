#ifndef SCOREGRAPHIC_H
#define SCOREGRAPHIC_H

#include "textgraphic.h"

class ScoreGraphic: public GraphicElement
{
private:
    TextGraphic *m_score;
    TextGraphic *m_prefixe;
    unsigned int m_showedScore;
public:
    ScoreGraphic(unsigned int zIndex, float x, float y, float rotateAngle, const sf::Font *font, unsigned int fontSize, unsigned int refreshPeriod, sf::Color color = sf::Color::Black, int style = 0);
    virtual ~ScoreGraphic();
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y);
    void setRotation(float angle);
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderTarget *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // SCOREGRAPHIC_H
