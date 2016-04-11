#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <SFML/Graphics.hpp>
#include <list>
#include "const.h"

class GraphicElement: public sf::Sprite
{
protected:
    std::pair<float, float> m_size;
    unsigned int m_zIndex;
    int m_nbLignes;
    int m_nbColonnes;
    int m_activeLigne;
    int m_activeColonne;
    void refreshTextRect();
public:
    GraphicElement() = default;
    GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, int nbLignes = 1, int nbColonnes = 1, int activeLigne = 1, int activeColonne = 1);
    virtual ~GraphicElement() = default;
    void rescale();
    void setSize(float width, float height);
    std::pair<float, float> getSize() const;
    unsigned int getZIndex() const;
    int getNbLignes() const;
    int getActiveColonne() const;
    virtual std::string getClassName() const;
    void setRectPos(int ligne, int colonne=1);
    bool operator<(const GraphicElement &ge) const;
    virtual void animate();
    virtual void setAnimatePeriod(float a);

    static std::map<std::string, sf::Texture*> m_listTextures;
    static void loadTextures(std::string themeName="Default");
    static void clearTextures();
};


#endif // GRAPHICELEMENT_H
