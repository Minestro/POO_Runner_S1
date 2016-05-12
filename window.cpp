#include "window.h"
#include <iostream>

Window::Window(std::string title, int style, float modelSizeW, float modelSizeH): Window::RenderWindow{}, m_title{title}, m_isFullScreen{0}
{
    sf::Vector2u size;
    size.x = sf::VideoMode::getDesktopMode().width;
    size.y = sf::VideoMode::getDesktopMode().height;
    this->create(sf::VideoMode(size.x, size.y), title, style);
    this->setVerticalSyncEnabled(0);
    this->setPosition(sf::Vector2i{0, 0});
    this->setView(sf::View{sf::FloatRect{0, 0, modelSizeW, modelSizeH}});
}

Window::~Window()
{
    GraphicElement::clearTextures();
    close();
}

sf::Event *Window::getEvent()
{
    return &m_event;
}

void Window::refreshSettings(AppSettings &settings)
{
    sf::Vector2u size;
    size.x = sf::VideoMode::getDesktopMode().width;
    size.y = sf::VideoMode::getDesktopMode().height;
    if (m_isFullScreen != settings.m_isFullScreen)
    {
        if (settings.m_isFullScreen)
        {
            m_isFullScreen = true;
            create(sf::VideoMode{size.x, size.y}, m_title, sf::Style::Fullscreen);
        } else {
            m_isFullScreen = false;
            create(sf::VideoMode{size.x, size.y}, m_title, sf::Style::Default);
        }
        setView(sf::View{sf::FloatRect{0, 0, GAME_SIZE_W, GAME_SIZE_H}});
    }
}
