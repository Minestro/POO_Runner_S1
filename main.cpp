#include <iostream>
#include "window.h"

using namespace std;

int main()
{
    Window::RenderWindow superfenetre{sf::VideoMode(800, 600, 32), "Runner", sf::Style::Close};
    while (true)
    {
        superfenetre.clear();
        superfenetre.display();
    }
    return 0;
}

