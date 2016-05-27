#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <math.h>
/*Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

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
    unsigned long int m_nextPatternAt;      //A quelle distance totale doit on ajouter un nouveau pattern d'obstacle
    void loadPatterns();
    float m_blurFade;

    void addElements();
    void moveElements();
    void collisionsTest();
    void checkEndGame();
    void magnetCoins(const GameCharacter *character);
    void refreshActivesPowers();

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
    const std::vector<std::pair<bool, std::chrono::time_point<std::chrono::system_clock> > > &getActivesPowers() const;
};

#endif // GAME_H
