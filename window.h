#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "graphicelement.h"

const int FPS = 60;

class Window: public sf::RenderWindow
{
private:
    sf::Event m_event;
    bool m_fullScreen;
public:
    Window()=default;
    Window(std::string title, int style);
    ~Window();
    sf::Event *getEvent();
    void saveConfig() const;
    void loadConfig();
};

#endif // WINDOW_H
