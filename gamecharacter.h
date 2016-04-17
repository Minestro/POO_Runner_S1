#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <math.h>
#include "movableelement.h"
#include "player.h"


class GameCharacter: public MovableElement
{
private:
    unsigned int m_score;
    bool m_movingLeft;
    bool m_movingRight;
    bool m_doubleJumpUsed;
    unsigned int m_life;
    bool m_doubleJumpActive;
    bool m_invincibilityActive;
    bool m_slowTimeActive;
    Player *m_player;
public:
    GameCharacter(float x, float y, float w, float h, float mx, float my, Player *player, unsigned int life = MAX_LIFE);
    virtual ~GameCharacter() = default;
    void addLife (unsigned int life);
    void removeLife (unsigned int life);
    unsigned int getLife() const;
    void jump();
    //void crouch(bool c); a voir plus tard
    void leftMove(bool ml);
    void rightMove(bool mr);
    void move() override;
    std::string getClassName() const;
};

#endif // GAMECHARACTER_H
