#include "game.h"
#include <iostream>
#include <time.h>

Game::Game(float width, float height, int movePeriodMs): Model::Model{width, height}, m_beginGameTime{}, m_lastObstacleCreate{}, m_movePeriod{movePeriodMs}, m_pauseTime{0}
{
    m_player =  new Player;
    GameCharacter *gc = new GameCharacter{0, HAUTEUR_SOL, 40, 40, 0, 0, m_player};
    m_characters.push_back(std::make_pair(1, gc));
    Background *b1 = new Background{"city_2.png", 1, 1.5, 1, 0};
    Background *b2 = new Background{"city_1.png", 2, 1.0, 1, 0};
    m_backgrounds.push_back(std::make_pair(1, b1));
    m_backgrounds.push_back(std::make_pair(1, b2));
}

Game::~Game()
{
    std::vector<std::pair<bool, Background *> >::iterator iterator = m_backgrounds.begin();
    while (iterator != m_backgrounds.end())
    {
        delete iterator->second;
        ++iterator;
    }
    std::vector<std::pair<bool, GameCharacter*> >::iterator iterator2 = m_characters.begin();
    while (iterator2 != m_characters.end())
    {
        delete iterator2->second;
        ++iterator2;
    }
    delete m_player;
}


float Game::getPixelSpeed() const
{
    return (((float) -PIXELPERBACKGROUNDMOVE / m_movePeriod) * 1000);
}

void Game::nextStep()
{
    srand(time(NULL));

    //On cherche le joueur 1 (le notre)
    std::vector<std::pair<bool, GameCharacter*> >::iterator player1 = getCharacters().begin();
    while (player1 != getCharacters().end() && player1->second->getId() != 0)
    {
        ++player1;
    }

    //On actualise la vitesse de defilement du background
    std::vector<std::pair<bool, Background *> >::iterator iterator = m_backgrounds.begin();
    while (iterator != m_backgrounds.end())
    {
        iterator->second->setMovePeriod(iterator->second->getCoefSpeed() * m_movePeriod);
        iterator->second->move();
        ++iterator;
    }

    //On bouge les personnages
    for (unsigned int i = 0; i<m_characters.size(); i++)
    {
        m_characters[i].second->move();

    }

    //On créé des nouveaux obstacles
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastObstacleCreate).count() > 2000)
    {
        int aleatoire= rand()% 2 ;
        if (aleatoire == 1)
        {
            Obstacle* ob = new Obstacle(GAME_SIZE_W, HAUTEUR_SOL- 30, 30,30, -PIXELPERBACKGROUNDMOVE, 0, m_movePeriod, 50, 1);
            m_obstacles.push_back(std::make_pair(1, ob));

        }
        m_lastObstacleCreate =  std::chrono::system_clock::now();
    }

    //Test des collisions avec les obstacles et les bonus
    std::vector<std::pair<bool, Obstacle *> >::iterator iterator1 = m_obstacles.begin();
    while (iterator1 != m_obstacles.end())
    {
        bool increment = true;
        iterator1->second->move();
        if (player1 != m_characters.end())
        {
            if (iterator1->second->collision(player1->second))
            {
                player1->second->removeLife(iterator1->second->getDammage());
                m_deletedElements.push_back(iterator1->second);
                m_obstacles.erase(iterator1);
                increment = false;
            }
        }
        if (iterator1->second->getPosition().first < -iterator1->second->getSize().first)
        {
            m_deletedElements.push_back(iterator1->second);
            m_obstacles.erase(iterator1);
            increment = false;
        }
        if (increment)
        {
            ++iterator1;
        }
    }

    //On test si un personnage n'a plus de vie
    for (unsigned int i=0; i<m_characters.size(); i++)
    {
        if (m_characters[i].second->getLife() == 0)
        {
            m_characters[i].second->setSate(character_state::DYING);
        }
    }
}

std::pair<float, float> Game::getCharacterSpeed(const GameCharacter *gc) const
{
    return {gc->getPixelSpeed().first - getPixelSpeed(), gc->getPixelSpeed().second};
}
