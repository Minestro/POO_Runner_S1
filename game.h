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
    std::chrono::time_point<std::chrono::system_clock> m_beginGameTime;
    std::chrono::time_point<std::chrono::system_clock> m_lastObstacleCreate;
    std::chrono::time_point<std::chrono::system_clock> m_lastMoveCall;
    int m_movePeriod;
    long int m_pauseTime;
    std::pair<int, int> m_size;
    GameCharacter *m_character;
    Player *m_player;
    std::vector<Background*> m_backgrounds;
    std::vector<Obstacle*> m_obstacles;
    std::vector<Bonus*> m_bonus;
    std::vector<const Element*> m_newElements;
    std::vector<const Element*> m_deletedElements;

public:
    Game(int movePeriodMs);
    ~Game();
    void nextStep();
    float getPixelSpeed() const;
    std::pair<int, int> getSize() const;
    std::vector<const Element*> &getDeletedElements();
    std::vector<const Element*> &getNewElements();
    GameCharacter *getCharacter();
};

#endif // GAME_H
