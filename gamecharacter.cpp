#include "gamecharacter.h"
#include <iostream>

GameCharacter::GameCharacter(float x, float y, float w, float h, float mx, float my, unsigned int life): MovableElement{x, y, w, h, mx, my}, m_movingLeft{0}, m_movingRight{0}, m_doubleJumpUsed{0}, m_life{life}, m_doubleJumpActive{1}, m_invincibilityActive{0}, m_slowTimeActive{0}
{

}

std::string GameCharacter::getClassName() const
{
    return "GameCharacter";
}

void GameCharacter::rightMove(bool mr)
{
    m_movingRight = mr;
}

void GameCharacter::leftMove(bool ml)
{
    m_movingLeft = ml;
}

void GameCharacter::jump()
{
    if (m_position.second + m_size.second == HAUTEUR_SOL || (m_doubleJumpActive && !m_doubleJumpUsed))
    {
        m_movement.second = -5;
        if (m_position.second + m_size.second != HAUTEUR_SOL)
        {
            m_doubleJumpUsed = 1;
        }
    }
}

/*void GameCharacter::crouch(bool c)
{
    if (c)
    {
        setSize(getSize().first, getSize().second/2);
    } else {
        setSize();
    }
}*/

void GameCharacter::move()
{
    if (m_movingLeft || m_movingRight)
    {
        if (m_movingRight && m_movement.first < CHARACTER_MAX_SPEED)
        {
            m_movement.first += ACCELERATION_CHARACTER;
        } else if (m_movingLeft && m_movement.first > -CHARACTER_MAX_SPEED)
        {
            m_movement.first -= ACCELERATION_CHARACTER;
        }
    } else {
        if (std::abs(m_movement.first) < ACCELERATION_CHARACTER)
        {
            m_movement.first = 0;
        }
        if (m_movement.first > 0)
        {
            m_movement.first -= (ACCELERATION_CHARACTER/2);
        } else if (m_movement.first < 0)
        {
            m_movement.first += (ACCELERATION_CHARACTER/2);
        } else if (std::abs(m_movement.first) < ACCELERATION_CHARACTER) {
            m_movement.first = 0;
        }
    }
    if (m_position.second + m_size.second < HAUTEUR_SOL)
    {
        m_movement.second += GRAVITY;
    }
    m_position.first += m_movement.first;
    m_position.second += m_movement.second;
    if (m_position.first + m_size.first > GAME_SIZE_W)
    {
        m_position.first = GAME_SIZE_W - m_size.first;
        m_movement.first = 0;
    } else if (m_position.first < 0)
    {
        m_position.first = 0;
        m_movement.first = 0;
    }
    if (m_position.second + m_size.second > HAUTEUR_SOL)
    {
        m_position.second = HAUTEUR_SOL - m_size.second;
        m_movement.second = 0;
        m_doubleJumpUsed = false;
    }
}
