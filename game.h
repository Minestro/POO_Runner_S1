#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>
#include "model.h"
#include "player.h"

class Game: public Model
{
private:
    std::chrono::time_point<std::chrono::system_clock> m_beginGameTime;
    std::chrono::time_point<std::chrono::system_clock> m_lastObstacleCreate;
    std::chrono::time_point<std::chrono::system_clock> m_lastMoveCall;
    int m_movePeriod;
    long int m_pauseTime;
    Player *m_player;

public:
    Game() = default;
    Game(float width, float height, int movePeriodMs);
    virtual ~Game();
    virtual std::pair<float, float> getCharacterSpeed(const GameCharacter *gc) const;
    void nextStep();
    float getPixelSpeed() const;
};

#endif // GAME_H
