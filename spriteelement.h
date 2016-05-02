#ifndef SPRITEELEMENT_H
#define SPRITEELEMENT_H

#include "graphicelement.h"
#include <chrono>

class SpriteElement: public GraphicElement, public sf::Sprite
{
protected:
    std::pair<float, float> m_size;
    int m_nbLignes;
    int m_nbColonnes;
    int m_activeLigne;
    int m_activeColonne;
    std::chrono::time_point<std::chrono::system_clock> m_lastAnimateCall;
    int m_animatePeriod;
    bool m_autoLoop;
    bool m_animationDirectionRight;
    void rescale(float width, float height);
public:
    SpriteElement() = default;
    SpriteElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Texture *texture, int animatePeriod = 0);
    SpriteElement(unsigned int zIndex, float width, float height, float x, float y, float rotateAngle, const sf::Texture *texture, int nbLignes, int nbColonnes, int activeLigne = 1, int activeColonne = 1, bool autoLoop = 1, int animatePeriod = 0, bool animationDirectionright = 1);
    virtual ~SpriteElement() = default;
    virtual std::pair<float, float> getSize() const;
    virtual std::pair<float, float> getPosition() const override;
    int getNbLignes() const;
    int getActiveColonne() const;
    virtual std::string getClassName() const;
    virtual void setSize(float width, float height);
    virtual void setPosition(float x, float y) override;
    virtual void setRotateAngle(float angle);
    void setRectPos(int ligne, int colonne=1);
    void setAutoLoop(bool autoLoop);
    void setNbLignes(int nb);
    void setNbColonnes(int nb);
    virtual void animate();
    void setAnimatePeriod(float a);
    void refreshTextRect();
    void changeDirectionSprite(bool directionRight);
    virtual void draw(sf::RenderWindow *window) const;
    virtual void refresh(const Element *el, Model *model);
};

#endif // SPRITEELEMENT_H
