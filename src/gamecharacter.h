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

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <math.h>
#include "movableelement.h"
#include "player.h"

enum character_state{ALIVE, DYING, DEAD};
enum character_id{PLAYER1 = 1, PLAYER2, PLAYER3, PLAYER4};

class Obstacle;

class GameCharacter: public MovableElement
{
private:
    static unsigned int nbCharacters;
    unsigned int m_score;
    bool m_movingLeft;
    bool m_movingRight;
    bool m_ascending;
    unsigned int m_life;
    int m_state;

    static Obstacle roof, ground, rightWall, leftWall;
public:
    GameCharacter(float x, float y, float w, float h, float mx, float my, unsigned int life = MAX_LIFE);
    virtual ~GameCharacter();
    void addLife (unsigned int life);
    void addScore(unsigned int score);
    void removeLife (unsigned int life);
    unsigned int getLife() const;
    unsigned int getScore() const;
    int getState() const;
    void setState(int state);
    void ascend(bool a);
    void leftMove(bool ml);
    void rightMove(bool mr);
    void move() override;
    std::string getClassName() const;
    static unsigned int getNbCharacters();
};

#endif // GAMECHARACTER_H
