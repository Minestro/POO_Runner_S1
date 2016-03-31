#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <SFML/Graphics.hpp>
#include <list>

const std::string FILES_LIST[] = {"city.png", "city_1.png", "city_2.png", "background.png", "character.png", "bonus.png", "buttons.png", "obstacles.png", "obstacles_block.png", "dead.png", "life.png", "logo.jpeg"};

class GraphicElement: public sf::Sprite
{
protected:
    std::pair<float, float> m_size;
    unsigned int m_zIndex;
public:
    GraphicElement() = default;
    GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture);
    GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, const sf::IntRect &textRect);
    virtual void rescale();
    void setSize(float width, float height);
    virtual void animate();
    std::pair<float, float> getSize() const;
    unsigned int getZIndex() const;
    bool operator==(const GraphicElement &ge) const;
    bool operator<(const GraphicElement &ge) const;

    static std::map<std::string, sf::Texture*> m_listTextures;
    static void loadTextures(std::string themeName="Default");
    static void clearTextures();
};


#endif // GRAPHICELEMENT_H
