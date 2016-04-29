#include "game.h"
#include <iostream>
#include <time.h>

Game::Game(float width, float height, unsigned int movePeriodMs): Model::Model{width, height}, m_beginGameTime{}, m_lastMove{}, m_lastAcceleration{}, m_movePeriod{movePeriodMs}, m_pauseTime{0}, m_distance{0}
{
    m_player =  new Player;
    GameCharacter *gc = new GameCharacter{0, HAUTEUR_SOL-40, 40, 40, 0, 0, m_player};
    m_characters.push_back(std::make_pair(1, gc));
    Background *b1 = new Background{"city_2.png", 1, 0.5, 1, 0};
    Background *b2 = new Background{"city_1.png", 2, 1.0, 1, 0};
    m_backgrounds.push_back(std::make_pair(1, b1));
    m_backgrounds.push_back(std::make_pair(1, b2));
    setSpeedPeriod(m_movePeriod);
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

//------------------------------------------------------------------------------
// Input:   Rien
// Output:  Rien
// Return:  Rien
// Purpose: Actualise tous les élements du modèle de jeu (déplacement des élements, test de collision, ajouts/ suppressions d'obstacles / bonus avant la prochaine actualisation de l'image
//------------------------------------------------------------------------------
void Game::nextStep()
{
    srand(time(nullptr));

    //On cherche le joueur 1 (le notre)
    std::vector<std::pair<bool, GameCharacter*> >::iterator player1 = getCharacters().begin();
    while (player1 != getCharacters().end() && player1->second->getId() != 0)
    {
        ++player1;
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastMove).count() >= m_movePeriod)
    {
        //On ajoute la distance
        m_distance += PIXELPERBACKGROUNDMOVE;
        for (unsigned int i = 0; i<m_characters.size(); i++)
        {
            if (m_characters[i].second->getState() != DYING)
            {
                m_characters[i].second->addScore(1);
            }
        }

        //On créé des nouveaux obstacles
        if ((m_distance/PIXELPERBACKGROUNDMOVE) % 100 == 0)
        {
            int aleatoire= rand()% 2 ;
            if (aleatoire == 1)
            {
                Obstacle* ob = new Obstacle(GAME_SIZE_W, HAUTEUR_SOL- 30, 30,30, -PIXELPERBACKGROUNDMOVE, 0, 0, 5, 1);
                m_obstacles.push_back(std::make_pair(1, ob));

            }
        }

        //On bouge les backgrounds
        for (unsigned int i = 0; i<m_backgrounds.size(); i++)
        {
            m_backgrounds[i].second->move();
        }

        //On bouge les personnages
        for (unsigned int i = 0; i<m_characters.size(); i++)
        {
            if(m_characters[i].second->getState() == character_state::DYING)
            {
                m_characters[i].second->setMovement(-PIXELPERBACKGROUNDMOVE, 0);
                m_characters[i].second->setMovePeriod(m_movePeriod);
            }
            m_characters[i].second->move();
        }

        //On bouge les obstacles
        for (unsigned int i = 0; i<m_obstacles.size(); i++)
        {
            m_obstacles[i].second->move();
        }

        m_lastMove = std::chrono::system_clock::now();
    }

    //Test des collisions avec les obstacles et les bonus
    std::vector<std::pair<bool, Obstacle *> >::iterator iterator1 = m_obstacles.begin();
    while (iterator1 != m_obstacles.end())
    {
        bool increment = true;
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

    //On augmente la vitesse
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-m_lastAcceleration).count() >= ACCELERATION_PERIOD)
    {
        setSpeedPeriod(--m_movePeriod);
        m_lastAcceleration = std::chrono::system_clock::now();
    }
}

std::pair<float, float> Game::getCharacterSpeed(const GameCharacter *gc) const
{
    return {gc->getPixelSpeed().first - getPixelSpeed(), gc->getPixelSpeed().second};
}

unsigned int Game::getSpeedPeriod() const
{
    return m_movePeriod;
}

void Game::setSpeedPeriod(int period)
{
    unsigned int mp;
    if (period < 1)
    {
        mp = 1;
    } else {
        mp = period;
    }
    m_movePeriod = mp;
}
