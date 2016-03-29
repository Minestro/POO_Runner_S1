#include "window.h"
#include <iostream>

Window::Window(std::string title, int style, float modelSizeW, float modelSizeH): Window::RenderWindow{}, m_fullScreen{0}
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
