#include "window.h"
#include <iostream>

Window::Window(std::string title, int style): Window::RenderWindow{}
{
    sf::Vector2u size;
    size.x = sf::VideoMode::getDesktopMode().width;
    size.y = sf::VideoMode::getDesktopMode().height;
    this->create(sf::VideoMode(size.x, size.y), title, style);
}
