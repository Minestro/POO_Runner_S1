#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "graphicelement.h"
#include "const.h"

class Window: public sf::RenderWindow
{
private:
    sf::Event m_event;
public:
    Window()=default;
    Window(std::string title, int style, float modelSizeW, float modelSizeH);
    ~Window();
    sf::Event *getEvent();
    void saveConfig() const;
    void loadConfig();
};

#endif // WINDOW_H
