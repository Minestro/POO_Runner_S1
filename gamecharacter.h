#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "movableelement.h"

const unsigned int MAX_LIFE = 100;

class GameCharacter: public MovableElement
{
private:
    unsigned int m_life;
    bool m_doubleJumpActive;
    bool m_invincibilityActive;
    bool m_slowTimeActive;
public:
    GameCharacter(float x, float y, float w, float h, float mx, float my, unsigned int life = MAX_LIFE);
    void addLife (unsigned int life) const;
    void removeLife (unsigned int life) const;
    void jump();
    void crouch();
    void leftMove();
    void rightMove();
    std::string getClassName() const override;
};

#endif // GAMECHARACTER_H
