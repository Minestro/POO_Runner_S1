#include "game.h"

using namespace tinyxml2;

Game::Game(float width, float height, unsigned int movePeriodMs): Model::Model{width, height}, m_beginGameTime{}, m_lastMove{}, m_lastAcceleration{}, m_movePeriod{movePeriodMs}, m_pauseTime{0}, m_player{nullptr}, m_distance{0}, m_powerActives{}, m_nextPatternAt{0}
{
    m_player =  new Player;
    GameCharacter *gc = new GameCharacter{GAME_SIZE_H/2, HAUTEUR_SOL-40, 100, 50, 0, 0, m_player};
    m_characters.push_back(std::make_pair(1, gc));
    Background *b1 = new Background{"FOND2.png", 1, 0.5, 1, 0};
    Background *b2 = new Background{"FOND1.png", 2, 1.0, 1, 0};
    m_backgrounds.push_back(std::make_pair(1, b1));
    m_backgrounds.push_back(std::make_pair(1, b2));

    setSpeedPeriod(m_movePeriod);
    m_powerActives.resize(power_list::NB_POWER - 1);

    int returnCode = loadPatterns();
    if (returnCode != XML_SUCCESS)
    {
        std::cerr << "Erreur lors de la lecture du fichier des definitions des obstacles. Code Erreur : " << returnCode << std::endl;
    }
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

int Game::loadPatterns()
{
    int nbPatterns = 0;
    int returnCode;
    XMLDocument patternsFile;
    returnCode = patternsFile.LoadFile(PATTERNS_FILE.c_str());
    if (returnCode != XML_SUCCESS)
    {
        return returnCode;
    }
    const XMLNode *pRoot = patternsFile.FirstChild();
    if (pRoot == nullptr)
    {
        return XML_ERROR_FILE_READ_ERROR;
    }
    const XMLElement *nbPatternsNode = pRoot->FirstChildElement("NbPatterns");
    if (nbPatternsNode == nullptr)
    {
        return XML_ERROR_PARSING_ELEMENT;
    }
    returnCode = nbPatternsNode->QueryIntText(&nbPatterns);
    if (returnCode != XML_SUCCESS)
    {
        return returnCode;
    }
    for (unsigned int i=0; (int)i<nbPatterns; i++)
    {
        ObstaclesBonusPattern op{i, this};
        returnCode = op.loadFromFile(patternsFile);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
        m_patternsList.push_back(op);
    }
    return XML_SUCCESS;
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

        //On créé des nouveaux obstacles et bonus en appelant un pattern aléatoire
        if (m_distance > m_nextPatternAt)
        {
            int ran = rand()% m_patternsList.size();
            m_patternsList[ran].addElementsToModel();
            m_nextPatternAt = m_distance + m_patternsList[ran].getWidth();
        }

        //On bouge les backgrounds
        for (unsigned int i = 0; i<m_backgrounds.size(); i++)
        {
            m_backgrounds[i].second->move();
        }

        //On bouge les obstacles
        for (unsigned int i = 0; i<m_obstacles.size(); i++)
        {
            m_obstacles[i].second->move();
        }

        //On bouge les bonus
        for (unsigned int i= 0; i<m_bonus.size(); i++)
        {
            m_bonus[i].second->move();
        }

        m_lastMove = std::chrono::system_clock::now();
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

    //Test des collisions avec les obstacles
    std::vector<std::pair<bool, Obstacle *> >::iterator obstacle = m_obstacles.begin();
    while (obstacle != m_obstacles.end())
    {
        bool increment = true;
        if (player1 != m_characters.end())
        {
            if (obstacle->second->collision(player1->second))
            {
                player1->second->removeLife(obstacle->second->getDammage());
                m_deletedElements.push_back(obstacle->second);
                m_obstacles.erase(obstacle);
                increment = false;
            }
        }
        if (obstacle->second->getPosition().first < -obstacle->second->getSize().first)
        {
            m_deletedElements.push_back(obstacle->second);
            m_obstacles.erase(obstacle);
            increment = false;
        }
        if (increment)
        {
            ++obstacle;
        }
    }

    //Test des collisions avec les bonus
    std::vector<std::pair<bool, Bonus *> >::iterator bonus = m_bonus.begin();   //Declaration d'un iterator pour parcourir les bonus
    while (bonus != m_bonus.end())          //Tant que on arrive pas à la fin de la liste de bonus
    {
        bool increment = true;              //Ce booléen indique si l'on a supprimé un bonus. Lorsqu'on supprime un bonus, tous les bonus suivants se retrouvent décalés du coup on incrémente pas l'iterator pour passer au bonus suivant
        if (bonus->second->getPosition().first < -bonus->second->getSize().first)   // Si le bonus sort de l'écran à gauche, on le supprime
        {
            m_deletedElements.push_back(bonus->second);
            m_bonus.erase(bonus);
            increment = false;
        }
        if (player1 != m_characters.end())      //Si le joueur 1 n'est pas mort (on test les collisions que pour lui)
        {
            if (bonus->second->collision(player1->second))      //Si il y a collision avec le personnage 1
            {
                switch (bonus->second->getType())               //Action différente suivant le type de bonus
                {
                case bonus_type::PIECE:
                    player1->second->addScore(1000);
                    break;
                case bonus_type::INVINSIBLE:
                    break;
                default:
                    break;
                }
                m_deletedElements.push_back(bonus->second);     //on supprime le bonus
                m_bonus.erase(bonus);
                increment = false;
            }
        }
        if (increment)                  //Si on a supprimé aucun bonus, on passe au suivant sinon pas besoin car les autres se sont trouvés décalés sur la position actuelle
        {
            ++bonus;
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
