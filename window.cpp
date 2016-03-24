#include "window.h"
#include <iostream>

Window::Window(std::string title, int style): Window::RenderWindow{}, m_fullScreen{0}
{
    GraphicElement::loadTextures();
    sf::Vector2u size;
    size.x = sf::VideoMode::getDesktopMode().width;
    size.y = sf::VideoMode::getDesktopMode().height;
    //loadConfig();
    if (m_fullScreen)
    {
        this->create(sf::VideoMode(size.x, size.y), title, sf::Style::Fullscreen);
    } else {
        this->create(sf::VideoMode(size.x, size.y), title, style);
    }
    this->setFramerateLimit(FPS);
    this->setPosition(sf::Vector2i{0, 0});
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
