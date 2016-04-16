#include "game.h"
#include <iostream>
#include <time.h>

Game::Game(int movePeriodMs): m_beginGameTime{}, m_lastObstacleCreate{}, m_lastMoveCall{}, m_movePeriod{movePeriodMs}, m_pauseTime{0}, m_size{std::pair<int, int>{GAME_SIZE_W, GAME_SIZE_H}}, m_backgrounds{}, m_obstacles{}, m_bonus{}, m_newElements{}, m_deletedElements{}
{
    m_character = new GameCharacter{0, HAUTEUR_SOL, 40, 40, 0, 0};
    m_newElements.push_back(m_character);
    Background *b1 = new Background{"city_2.png", 1, 1.5, 0, 0};
    Background *b2 = new Background{"city_1.png", 2, 1.0, 0, 0};
    m_newElements.push_back(b1);
    m_backgrounds.push_back(b1);
    m_newElements.push_back(b2);
    m_backgrounds.push_back(b2);
}

Game::~Game()
{
    std::vector<Background *>::iterator iterator = m_backgrounds.begin();
    while (iterator != m_backgrounds.end())
    {
        delete (*iterator);
        ++iterator;
    }
    delete m_character;
}

std::vector<const Element*> &Game::getDeletedElements()
{
    return m_deletedElements;
}

std::vector<const Element*> &Game::getNewElements()
{
    return m_newElements;
}

std::pair<int, int> Game::getSize() const
{
    return m_size;
}

GameCharacter *Game::getCharacter()
{
    return m_character;
}

float Game::getPixelSpeed() const
{
    return (((float) -PIXELPERBACKGROUNDMOVE / m_movePeriod) * 1000);
}

void Game::nextStep()
{
    srand(time(NULL));
    std::vector<Background *>::iterator iterator = m_backgrounds.begin();
    while (iterator != m_backgrounds.end())
    {
        (**iterator).setMovePeriod((**iterator).getCoefSpeed() * m_movePeriod);
        (**iterator).move();
        ++iterator;
    }
    m_lastMoveCall = std::chrono::system_clock::now();
    m_character->move();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastObstacleCreate).count() > 2000)
    {
        int aleatoire= rand()% 2 ;
        if (aleatoire == 1)
        {
            Obstacle* ob = new Obstacle(GAME_SIZE_W, HAUTEUR_SOL- 30, 30,30, -PIXELPERBACKGROUNDMOVE, 0, m_movePeriod, 5, 1);
            m_obstacles.push_back(ob);
            m_newElements.push_back(ob);

        }
        m_lastObstacleCreate=  std::chrono::system_clock::now();
    }
    std::vector<Obstacle *>::iterator iterator1 = m_obstacles.begin();
    while (iterator1 != m_obstacles.end())
    {
        (**iterator1).move();
        if ((**iterator1).collision(m_character))
        {
            m_character->removeLife((**iterator1).getDammage());
            m_deletedElements.push_back(*iterator1);
            m_obstacles.erase(iterator1);
        } else if ((**iterator1).getPosition().first < -(**iterator1).getSize().first)
        {
            m_deletedElements.push_back(*iterator1);
            m_obstacles.erase(iterator1);
        } else
        {
            ++iterator1;
        }
    }
}
