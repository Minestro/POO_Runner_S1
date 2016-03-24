#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H
#define BACKGROUND_TEXTURE 0
#define BUTTON_TEXTURE 1

#include <SFML/Graphics.hpp>
#include <list>

const std::string FILES_LIST[] = {"city.png", "background.png"};

class GraphicElement: public sf::Sprite
{
private:
    std::pair<float, float> m_size;
    unsigned int m_zIndex;
public:
    GraphicElement() = default;
    GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture);
    GraphicElement(unsigned int zIndex, float width, float height, float x, float y, const sf::Texture *texture, const sf::IntRect &textRect);
    void rescale();
    void setSize(float width, float height);
    std::pair<float, float> getSize() const;
    unsigned int getZIndex() const;
    bool operator==(const GraphicElement &ge) const;
    bool operator<(const GraphicElement &ge) const;

    static std::vector<sf::Texture*> m_listTextures;
    static void loadTextures(std::string themeName="Default");
    static void clearTextures();
};


#endif // GRAPHICELEMENT_H
