#ifndef SPRITEELEMENT_H
#define SPRITEELEMENT_H

#include "graphicelement.h"

class SpriteElement: public GraphicElement, public sf::Sprite
{
protected:
    unsigned int m_nbLignes;
    unsigned int m_nbColonnes;
    unsigned int m_activeLigne;
    unsigned int m_activeColonne;
    std::chrono::time_point<std::chrono::system_clock> m_lastAnimateCall;
    unsigned int m_animatePeriod;
    bool m_autoLoop;
    bool m_animationDirectionRight;
    void rescale(float width, float height);
public:
    SpriteElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Texture *texture, unsigned int animatePeriod = 0);
    SpriteElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Texture *texture, unsigned int nbLignes, unsigned int nbColonnes, unsigned int activeLigne = 1, unsigned int activeColonne = 1, bool autoLoop = 1, unsigned int animatePeriod = 0, bool animationDirectionright = 1);
    virtual ~SpriteElement() = default;
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const override;
    int getNbLignes() const;
    int getActiveColonne() const;
    virtual std::string getClassName() const;
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    void setRectPos(int ligne, int colonne=1);
    void setAutoLoop(bool autoLoop);
    void setNbLignes(unsigned int nb);
    void setNbColonnes(unsigned int nb);
    void setAnimatePeriod(unsigned int a);
    virtual void animate();
    void refreshTextRect();
    void changeDirectionSprite(bool directionRight);
    virtual void draw(sf::RenderTarget *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // SPRITEELEMENT_H
