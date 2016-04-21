#ifndef SCOREGRAPHIC_H
#define SCOREGRAPHIC_H

#include "textelement.h"

class ScoreGraphic: public GraphicElement
{
private:
    TextElement *m_score;
    TextElement *m_prefixe;
    unsigned int m_showedScore;
public:
    ScoreGraphic() = default;
    ScoreGraphic(unsigned int zIndex, float x, float y, const sf::Font *font, unsigned int fontSize, int refreshPeriod, sf::Color color = sf::Color::Black, int style = 0);
    virtual ~ScoreGraphic();
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y);
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const;
    virtual std::string getClassName() const;
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // SCOREGRAPHIC_H
