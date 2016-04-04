#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>
#include "gamecharacter.h"
#include "player.h"
#include "obstacle.h"
#include "bonus.h"
#include "background.h"
#include "const.h"

class Game
{
private:
    unsigned int m_score;
    int m_speedPeriod;
    std::chrono::time_point<std::chrono::system_clock> m_lastNextStepCall;
    std::chrono::time_point<std::chrono::system_clock> m_beginGameTime;
    int m_pauseTime;
    std::pair<int, int> m_size;
    GameCharacter *m_character;
    Player *m_player;
    std::vector<Background*> m_backgrounds;
    std::vector<Obstacle*> m_obstacles;
    std::vector<Bonus*> m_bonus;
    std::vector<const Element*> m_newElements;
    std::vector<const Element*> m_deletedElements;

public:
    Game();
    ~Game();
    void nextStep();
    std::pair<int, int> getSize() const;
    std::vector<const Element*> &getDeletedElements();
    std::vector<const Element*> &getNewElements();
    GameCharacter *getCharacter();
};

#endif // GAME_H
