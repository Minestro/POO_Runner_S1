#include "gamecharacter.h"
#include <iostream>

unsigned int GameCharacter::nbCharacters = 0;

GameCharacter::GameCharacter(float x, float y, float w, float h, float mx, float my, Player *player, unsigned int life, unsigned int id): MovableElement{x, y, w, h, 0.0f, mx, my, 0.0f, CHARACTERSPEEDPERIOD}, m_score{0}, m_movingLeft{0}, m_movingRight{0}, m_ascending{0}, m_life{life}, m_player{player}, m_id{id}, m_state{character_state::STATIC}
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

unsigned int GameCharacter::getId() const
{
    return m_id;
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
        }

        //On deplace la position de la balle
        m_position.first += m_movement.first;
        m_position.second += m_movement.second;

        if (m_state != character_state::DYING)
        {
            //Test des collisions avec les bords de l'écran et le sol
            if (m_position.first + m_size.first > GAME_SIZE_W)
            {
                m_position.first = GAME_SIZE_W - m_size.first;
                m_movement.first = 0;
            } else if (m_position.first < 0)
            {
                m_position.first = 0;
                m_movement.first = 0;
            }
            if (m_position.second + m_size.second > GAME_SIZE_H)
            {
                m_position.second = GAME_SIZE_H - m_size.second;
                m_movement.second = 0;
            } else if (m_position.second < 0)
            {
                m_position.second = 0;
                m_movement.second = 0;
            }
        }

        //On rotate l'avion suivant sont vecteur de deplacement y
        m_rotation = (m_movement.second/CHARACTER_MAX_SPEED)*45;
        if (m_rotation > 45)
        {
            m_rotation = 45;
        } else if (m_rotation < -45)
        {
            m_rotation = -45;
        }

        m_lastMoveCall = std::chrono::system_clock::now();
    }
}

