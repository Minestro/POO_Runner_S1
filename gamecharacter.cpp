#include "gamecharacter.h"

GameCharacter::GameCharacter(float x, float y, float w, float h, float mx, float my, unsigned int life): MovableElement::MovableElement{x, y, w, h, mx, my}, m_life{life}, m_doubleJumpActive{0}, m_invincibilityActive{0}, m_slowTimeActive{0}
{

}

std::string GameCharacter::getClassName() const
{
    return "GameCharacter";
}
