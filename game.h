#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>
#include "gamecharacter.h"
#include "player.h"
#include "movableelement.h"

class Game
{
private:
    unsigned int m_score;
    std::time_t m_startTime;
    GameCharacter *m_character;
    Player *m_player;
    std::vector<*MovableElement> m_objects;

public:

};

#endif // GAME_H
