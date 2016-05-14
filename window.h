#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include "graphicelement.h"
#include "const.h"
#include "appsettings.h"

class Window: public sf::RenderWindow
{
private:
    sf::Event m_event;
    std::string m_title;
    bool m_isFullScreen;
public:
    Window(std::string title, int style, float modelSizeW, float modelSizeH);
    ~Window();
    sf::Event *getEvent();
    void saveConfig() const;
    void refreshSettings(AppSettings &settings);
};

#endif // WINDOW_H
