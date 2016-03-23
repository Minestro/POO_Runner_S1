#include <iostream>
#include "window.h"

using namespace std;

int main()
{
    Window superfenetre{"kikou", sf::Style::Default};
    while (true)
    {
        superfenetre.clear();
        superfenetre.display();
    }
    return 0;
}

