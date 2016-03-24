#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>
#include "gamecharacter.h"
#include "player.h"
#include "obstacle.h"
#include "bonus.h"

const int GAME_SIZE_W = 800;
const int GAME_SIZE_H = 600;

class Game
{
private:
    unsigned int m_score;
    std::pair<float, float> m_size;
    std::time_t m_gameTime;
    GameCharacter *m_character;
    Player *m_player;
    std::vector<Obstacle*> m_obstacles;
    std::vector<Bonus*> m_bonus;
    std::vector<const Element*> m_newElements;
    std::vector<const Element*> m_deletedElements;

public:
    Game();
    void nextStep();
    std::vector<const Element*> &getDeletedElements();
    std::vector<const Element*> &getNewElements();
};

#endif // GAME_H
