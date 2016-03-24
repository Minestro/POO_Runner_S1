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
public:
    GraphicElement() = default;
    GraphicElement(float width, float height, float x, float y, const sf::Texture &texture);
    void rescale();
    void setSize(float width, float height);
    static std::vector<sf::Texture*> m_listTextures;
    static void loadTextures(std::string themeName="Default");
    static void clearTextures();
};


#endif // GRAPHICELEMENT_H
