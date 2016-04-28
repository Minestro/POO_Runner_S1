#include "spriteelement.h"

SpriteElement::SpriteElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, int animatePeriod, int nbLignes, int nbColonnes, int activeLigne, int activeColonne,  bool autoLoop, bool animationDirectionright) : GraphicElement{zIndex}, sf::Sprite{}, m_size{width, height}, m_nbLignes{nbLignes}, m_nbColonnes{nbColonnes}, m_activeLigne{activeLigne}, m_activeColonne{activeColonne}, m_lastAnimateCall{}, m_animatePeriod{animatePeriod}, m_autoLoop{autoLoop}, m_animationDirectionRight{animationDirectionright}
{
    setTexture(*texture);
    setPosition(x, y);
    refreshTextRect();
    rescale(width , height);
}

void SpriteElement::rescale(float width, float height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float height_factor = height / bb.height;
    float width_factor;
    if (getTexture()->isRepeated())
    {
        width_factor = (width / bb.width) * 2;
    } else {
        width_factor = width / bb.width;
    }
    setScale(width_factor, height_factor);
}

std::pair<float, float> SpriteElement::getSize() const
{
    return m_size;
}

std::pair<float, float> SpriteElement::getPosition() const
{
    return {sf::Sprite::getPosition().x, sf::Sprite::getPosition().y};
}

int SpriteElement::getNbLignes() const
{
    return m_nbLignes;
}

int SpriteElement::getActiveColonne() const
{
    return m_activeColonne;
}

std::string SpriteElement::getClassName() const
{
    return "SpriteElement";
}

void SpriteElement::setSize(float width, float height)
{
    m_size.first = width;
    m_size.second = height;
    rescale(m_size.first, m_size.second);
}

void SpriteElement::setRectPos(int ligne, int colonne)
{
    m_activeColonne = colonne;
    m_activeLigne = ligne;
    if (m_nbLignes > 1 || m_nbColonnes > 1)
    {
        refreshTextRect();
    }
}

void SpriteElement::setAutoLoop(bool autoLoop)
{
    m_autoLoop = autoLoop;
}

void SpriteElement::setNbColonnes(int nb)
{
    m_nbColonnes = nb;
}

void SpriteElement::setNbLignes(int nb)
{
    m_nbLignes = nb;
}

void SpriteElement::changeDirectionSprite(bool directionRight)
{
    m_animationDirectionRight = directionRight;
}

void SpriteElement::animate()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastAnimateCall).count() >= m_animatePeriod)
    {
        if (m_animationDirectionRight)
        {
            if ((m_activeColonne%m_nbColonnes) > 0 )
            {
                setRectPos(m_activeLigne, ++m_activeColonne);
            }
            else if (m_autoLoop)
            {
                setRectPos(m_activeLigne, 1);
            }
        } else {
            if (m_activeColonne > 1)
            {
                setRectPos(m_activeLigne, --m_activeColonne);
            }
            else if (m_autoLoop)
            {
                setRectPos(m_activeLigne, m_nbColonnes);
            }
        }
        m_lastAnimateCall = std::chrono::system_clock::now();
    }
}

void SpriteElement::setAnimatePeriod(float a)
{
    m_animatePeriod = a;
}

void SpriteElement::refreshTextRect()
{
    setTextureRect(sf::IntRect{(int)((m_activeColonne-1) * (getTexture()->getSize().x / m_nbColonnes)), (int) ((m_activeLigne-1) * (getTexture()->getSize().y / m_nbLignes)), (int)getTexture()->getSize().x / m_nbColonnes, (int)getTexture()->getSize().y / m_nbLignes});
}

void SpriteElement::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}

void SpriteElement::setPosition(float x, float y)
{
    sf::Sprite::setPosition(x, y);
}

void SpriteElement::refresh(const Element *el, Model *model)
{
    (void) model;
    setSize(el->getSize().first, el->getSize().second);
    setPosition(el->getPosition().first, el->getPosition().second);
    animate();
}

