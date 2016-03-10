#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "movableelement.h"

class GameCharacter:MovableElement
{
private:
    unsigned int m_life;

public:
    void addLife (unsigned int life) const;
    void removeLife (unsigned int life) const;
};

#endif // GAMECHARACTER_H
