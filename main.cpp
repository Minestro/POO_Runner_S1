#include <iostream>
#include "window.h"

using namespace std;

int main()
{
    bool yolo = true;
    Window superfenetre{"kikou", sf::Style::Default};
    sf::Event event;
    while (yolo)
    {
        while (superfenetre.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                superfenetre.close();
                yolo = false;
            }
        }
        superfenetre.clear();
        superfenetre.display();
    }
    return 0;
}
