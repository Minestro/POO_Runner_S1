#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "movableelement.h"
#include "const.h"

class GameCharacter: public MovableElement
{
private:
    bool m_movingLeft;
    bool m_movingRight;
    bool m_doubleJumpUsed;
    unsigned int m_life;
    bool m_doubleJumpActive;
    bool m_invincibilityActive;
    bool m_slowTimeActive;
public:
    GameCharacter(float x, float y, float w, float h, float mx, float my, unsigned int life = MAX_LIFE);
    void addLife (unsigned int life) const;
    void removeLife (unsigned int life) const;
    void jump();
    //void crouch(bool c); a voir plus tard
    void leftMove(bool ml);
    void rightMove(bool mr);
    void move() override;
    std::string getClassName() const;
};

#endif // GAMECHARACTER_H
