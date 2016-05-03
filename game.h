#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "model.h"
#include "player.h"
#include "obstaclesbonuspattern.h"

class Game: public Model
{
private:
    std::chrono::time_point<std::chrono::system_clock> m_beginGameTime;
    std::chrono::time_point<std::chrono::system_clock> m_lastMove;
    std::chrono::time_point<std::chrono::system_clock> m_lastAcceleration;
    unsigned int m_movePeriod;
    long int m_pauseTime;
    Player *m_player;
    unsigned long int m_distance;
    std::vector<std::pair <bool, std::chrono::time_point<std::chrono::system_clock> > > m_powerActives; //Pour chaque pouvoir on associ un bool pour savoir si il est activé et un time point qui définit jusqu'à quand le pouvoir est actif.
    std::vector<ObstaclesBonusPattern> m_patternsList;
    unsigned long int m_nextPatternAt;
    int loadPatterns();

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
