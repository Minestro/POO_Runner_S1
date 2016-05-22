#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "player.h"
#include "elementslist.h"
#include "menu.h"

enum game_state{INTRO, RUNNING};
enum game_mode{SOLO, MULTI_HOSTING, MULTI_CLIENT};

class Game: public Model
{
private:
    bool m_pause;
    int m_gameState;
    int m_gameMode;
    std::chrono::time_point<std::chrono::system_clock> m_lastMove;
    std::chrono::time_point<std::chrono::system_clock> m_lastAcceleration;
    unsigned int m_movePeriod;
    Player *m_player;
    unsigned long int m_distance;
    std::vector<std::pair <bool, std::chrono::time_point<std::chrono::system_clock> > > m_powerActives; //Pour chaque pouvoir on associ un bool pour savoir si il est activé et un time point qui définit jusqu'à quand le pouvoir est actif.
    std::vector<ElementsList> m_patternsList;
    unsigned long int m_nextPatternAt;
    void loadPatterns();
    float m_blurFade;

    void addElements();
    void moveElements();
    void collisionsTest();
    void checkEndGame();

public:
    Game(float width, float height, App *app);
    virtual ~Game();
    void nextStep();
    float getPixelSpeed() const;
    unsigned long int getDistance() const;
    unsigned int getSpeedPeriod() const;
    int getGameState() const;
    int getGameMode() const;
    float getBlurFade() const;
    virtual std::string getClassName() const;
    Player *getPlayer();
    void setGameState(int state);
    void setGameMode(int mode);
    void setSpeedPeriod(int period);
    void setPlayer(Player *player);
    bool isPause() const;
    void setPause(bool a);
    void resetGame();
    GameCharacter *getCharacterById(unsigned int id);
};

#endif // GAME_H
