
#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <math.h>
#include "movableelement.h"
#include "player.h"

enum character_state{ALIVE, DYING};
enum character_id{PLAYER1 = 1, PLAYER2, PLAYER3, PLAYER4};

class GameCharacter: public MovableElement
{
private:
    static unsigned int nbCharacters;
    unsigned int m_score;
    bool m_movingLeft;
    bool m_movingRight;
    bool m_ascending;
    unsigned int m_life;
    Player *m_player;
    character_state m_state;
public:
    GameCharacter(float x, float y, float w, float h, float mx, float my, Player *player, unsigned int life = MAX_LIFE);
    virtual ~GameCharacter();
    void addLife (unsigned int life);
    void addScore(unsigned int score);
    void removeLife (unsigned int life);
    unsigned int getLife() const;
    unsigned int getScore() const;
    character_state getState() const;
    void setSate(character_state state);
    void ascend(bool a);
    void leftMove(bool ml);
    void rightMove(bool mr);
    void move() override;
    std::string getClassName() const;
    static unsigned int getNbCharacters();
};

#endif // GAMECHARACTER_H
