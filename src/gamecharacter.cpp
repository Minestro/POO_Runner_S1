#include "gamecharacter.h"
#include <iostream>
#include "obstacle.h"

unsigned int GameCharacter::nbCharacters = 0;

GameCharacter::GameCharacter(float x, float y, float w, float h, float mx, float my, Player *player, unsigned int life): MovableElement{x, y, w, h, 0.0f, mx, my, 0.0f, CHARACTERSPEEDPERIOD}, m_score{0}, m_movingLeft{0}, m_movingRight{0}, m_ascending{0}, m_life{life}, m_player{player}, m_state{character_state::ALIVE}
{
    GameCharacter::nbCharacters ++;
}

GameCharacter::~GameCharacter()
{
    GameCharacter::nbCharacters --;
}

std::string GameCharacter::getClassName() const
{
    return "GameCharacter";
}

void GameCharacter::rightMove(bool mr)
{
    if (m_state != character_state::DYING)
    {
        m_movingRight = mr;
    }
}

void GameCharacter::leftMove(bool ml)
{
    if (m_state != character_state::DYING)
    {
        m_movingLeft = ml;
    }
}

void GameCharacter::ascend(bool a)
{
    if (m_state != character_state::DYING)
    {
        m_ascending = a;
    }
}

unsigned int GameCharacter::getLife() const
{
    return m_life;
}

void GameCharacter::removeLife(unsigned int life)
{
    if ((int)(m_life - life) < 0)
    {
        m_life = 0;
    } else {
        m_life -= life;
    }
}

unsigned int GameCharacter::getNbCharacters()
{
    return GameCharacter::nbCharacters;
}

unsigned int GameCharacter::getScore() const
{
    return m_score;
}

void GameCharacter::addScore(unsigned int score)
{
    m_score += score;
}

character_state GameCharacter::getState() const
{
    return m_state;
}

void GameCharacter::setSate(character_state state)
{
    m_state = state;
}

void GameCharacter::move()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastMoveCall).count() >= m_movePeriod)
    {
        Obstacle rightWall{MODEL_SIZE_W, 0, 1, MODEL_SIZE_H, 0, 0, 0, 0, 0, 0, -1};
        Obstacle leftWall {-1, 0, 1, MODEL_SIZE_H, 0, 0, 0, 0, 0, 0, -1};
        Obstacle roof{0, -1, MODEL_SIZE_W, 1, 0, 0, 0, 0, 0, 0, -1};
        Obstacle ground{0, HAUTEUR_SOL, MODEL_SIZE_W, 1, 0, 0, 0, 0, 0, 0, -1};
        if (m_state != character_state::DYING)
        {
            //On déplace latéralement le personnage
            if (m_movingRight && m_movement.first < CHARACTER_MAX_SPEED)
            {
                m_movement.first += ACCELERATION_CHARACTER;
            } else if (m_movingLeft && m_movement.first > -CHARACTER_MAX_SPEED)
            {
                m_movement.first -= ACCELERATION_CHARACTER;
            }

            //Si le vecteur mouvement x est supérieur à 0, on décelère la balle
            if (m_movement.first > 0)
            {
                m_movement.first -= (ACCELERATION_CHARACTER/2);
            } else if (m_movement.first < 0)
            {
                m_movement.first += (ACCELERATION_CHARACTER/2);
            }

            // Si la balle est en lair, on applique la gravité
            if (!m_ascending)
            {
                m_movement.second += GRAVITY;
            } else if (m_ascending && m_movement.second > -CHARACTER_MAX_SPEED)
            {
                m_movement.second -= GRAVITY;
            }

            if (!m_movingLeft && !m_movingRight && abs(m_movement.first) < ACCELERATION_CHARACTER)
            {
                m_movement.first = 0;
            }

            //Test des collisions avec les bords de l'écran et le sol
            if (collision(&rightWall) && m_movement.first > 0)
            {
                m_movement.first = 0;
                m_position.first --;
            } else if (collision(&leftWall) && m_movement.first < 0)
            {
                m_movement.first = 0;
                m_position.first ++;
            }

            if (collision(&ground) && m_movement.second > 0)
            {
                m_life = 0;
                m_movement.second = 0;
            } else if (collision(&roof) && m_movement.second < 0)
            {
                if (m_rotation < 0)
                {
                    m_rotation ++;
                    while (!collision(&roof))
                    {
                        m_position.second --;
                    }
                } else if (m_rotation > 0)
                {
                    m_rotation --;
                    while (!collision(&roof))
                    {
                        m_position.second --;
                    }
                }
                if (abs(m_rotation) < 1)
                {
                    m_rotation = 0;
                }
                m_movement.second = 0;
            }
        }

        //On rotate l'avion suivant sont vecteur de deplacement y
        if ((!collision(&roof) && !collision(&ground)) || m_state != character_state::ALIVE)
        {
            float rotation = (m_movement.second/CHARACTER_MAX_SPEED)*45;
            if (rotation > 45)
            {
                rotation = 45;
            } else if (rotation < -45)
            {
                rotation = -45;
            }
            if (m_state == character_state::DYING)
            {
                m_rotation = rotation;
            }
            if (m_rotation < rotation)
            {
                m_rotation ++;
            } else if (m_rotation > rotation)
            {
                m_rotation --;
            }
        }

        //On deplace la position de la balle
        m_position.first += m_movement.first;
        m_position.second += m_movement.second;

        m_lastMoveCall = std::chrono::system_clock::now();
    }
}

 void GameCharacter::addLife (unsigned int life)
 {
     m_life+=life;
     if (m_life > 100)
     {
         m_life = 100;
     }
 }