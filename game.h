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
    std::chrono::time_point<std::chrono::system_clock> m_lastMove;
    unsigned int m_movePeriod;
    long int m_pauseTime;
    Player *m_player;
    unsigned long int m_distance;

public:
    Game() = default;
    Game(float width, float height, unsigned int movePeriodMs);
    virtual ~Game();
    virtual std::pair<float, float> getCharacterSpeed(const GameCharacter *gc) const;
    void nextStep();
    float getPixelSpeed() const;
    unsigned long int getDistance() const;
    unsigned int getSpeedPeriod() const;
    void setSpeedPeriod(int period);
};

#endif // GAME_H
