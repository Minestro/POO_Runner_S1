#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <math.h>
#include "movableelement.h"
#include "player.h"

enum character_state{STATIC, DYING, RUNNING, FLYING};

class GameCharacter: public MovableElement
{
private:
    static unsigned int nbCharacters;
    unsigned int m_score;
    bool m_movingLeft;
    bool m_movingRight;
    bool m_doubleJumpUsed;
    unsigned int m_life;
    bool m_doubleJumpActive;
    bool m_invincibilityActive;
    bool m_slowTimeActive;
    Player *m_player;
    unsigned int m_id;
    character_state m_state;
public:
    GameCharacter(float x, float y, float w, float h, float mx, float my, Player *player, unsigned int life = MAX_LIFE, unsigned int id = GameCharacter::nbCharacters);
    virtual ~GameCharacter();
    void addLife (unsigned int life);
    void removeLife (unsigned int life);
    unsigned int getLife() const;
    unsigned int getId() const;
    unsigned int getScore() const;
    character_state getState() const;
    void setSate(character_state state);
    void addScore(unsigned int score);
    void jump();
    //void crouch(bool c); a voir plus tard
    void leftMove(bool ml);
    void rightMove(bool mr);
    void move() override;
    std::string getClassName() const;
    static unsigned int getNbCharacters();
};

#endif // GAMECHARACTER_H
