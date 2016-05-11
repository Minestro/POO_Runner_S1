#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "model.h"
#include "player.h"
#include "obstaclesbonuspattern.h"

#define GAMEINTROTEXTID 6354354

enum game_state{INTRO, RUNNING};
enum game_mode{SOLO, MULTI_HOSTING, MULTI_CLIENT};

class Game: public Model
{
private:
    int m_gameState;
    int m_gameMode;
    std::chrono::time_point<std::chrono::system_clock> m_lastMove;
    std::chrono::time_point<std::chrono::system_clock> m_lastAcceleration;
    unsigned int m_movePeriod;
    Player *m_player;
    unsigned long int m_distance;
    std::vector<std::pair <bool, std::chrono::time_point<std::chrono::system_clock> > > m_powerActives; //Pour chaque pouvoir on associ un bool pour savoir si il est activé et un time point qui définit jusqu'à quand le pouvoir est actif.
    std::vector<ObstaclesBonusPattern> m_patternsList;
    unsigned long int m_nextPatternAt;
    int loadPatterns();

public:
    Game(float width, float height, unsigned int movePeriodMs);
    virtual ~Game();
    virtual std::pair<float, float> getCharacterSpeed(const GameCharacter *gc) const;
    void nextStep();
    float getPixelSpeed() const;
    unsigned long int getDistance() const;
    unsigned int getSpeedPeriod() const;
    int getGameState() const;
    int getGameMode() const;
    void setGameState(int state);
    void setGameMode(int mode);
    void setSpeedPeriod(int period);
};

#endif // GAME_H
