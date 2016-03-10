#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>

class Window: public sf::RenderWindow
{
private:

public:
    Window(std::string title, int style);
    void saveConfig() const;
    void loadConfig();
};

#endif // WINDOW_H
