#include "game.h"
#include "app.h"

using namespace tinyxml2;

Game::Game(float width, float height, App *app): Model::Model{width, height, app}, m_pause{false}, m_gameMode{game_mode::SOLO}, m_lastMove{}, m_lastAcceleration{}, m_movePeriod{STARTSPEEDPERIODGAME}, m_player{nullptr}, m_distance{0}, m_powerActives{}, m_nextPatternAt{0}, m_blurFade{0.0f}
{
    resetGame();
    m_powerActives.resize(power_list::NB_POWER - 1);

    try
    {
        loadPatterns();
    }
    catch (const XMLError &er)
    {
        std::cout << "Erreur lord de la lecture de " << PATTERNS_FILE << " Code erreur : " <<  std::to_string(er) << std::endl;
        m_app->getMenuModel().exitApp();
    }

}

Game::~Game()
{
    if (m_player != nullptr)
    {
        delete m_player;
    }
}

void Game::setPlayer(Player *player)
{
    if (m_player != nullptr && m_player != player)    //Qu'un seul profil à la fois si on le remplace on supprime l'ancien.
    {
        delete m_player;
    }
    m_player = player;
}

void Game::loadPatterns()
{
    int nbPatterns = 0;
    int returnCode;
    XMLDocument patternsFile;
    returnCode = patternsFile.LoadFile(PATTERNS_FILE.c_str());
    if (returnCode != XML_SUCCESS)
    {
        throw XMLError(returnCode);
    }
    const XMLNode *pRoot = patternsFile.FirstChild();
    if (pRoot == nullptr)
    {
        throw XMLError (XML_ERROR_FILE_READ_ERROR);
    }
    const XMLElement *nbPatternsNode = pRoot->FirstChildElement("NbPatterns");
    if (nbPatternsNode == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    returnCode = nbPatternsNode->QueryIntText(&nbPatterns);
    if (returnCode != XML_SUCCESS)
    {
        throw XMLError (returnCode);
    }
    for (unsigned int i=0; (int)i<nbPatterns; i++)
    {
        ElementsList op{i};
        op.loadFromFile(patternsFile, this);
        m_patternsList.push_back(op);
    }
}

float Game::getPixelSpeed() const
{
    return (((float) -PIXELPERBACKGROUNDMOVE / m_movePeriod) * 1000);
}

//------------------------------------------------------------------------------
// Input:   Rienb1
// Output:  Rien
// Return:  Rien
// Purpose: Actualise tous les élements du modèle de jeu (déplacement des élements, test de collision, ajouts/ suppressions d'obstacles / bonus avant la prochaine actualisation de l'image
//------------------------------------------------------------------------------
void Game::nextStep()
{
    if (m_app->getMenuModel().getActivePage() == menuPage::ESCAPE_MENU && (m_gameState == game_state::RUNNING || m_gameState == game_state::INTRO) && !m_pause && getCharacterById(character_id::PLAYER1)->getState() == character_state::ALIVE)
    {
        m_app->getSound().setCharacterSoundPlay(1);
    } else {
        m_app->getSound().setCharacterSoundPlay(0);
    }

    //Effet de blur
    if (m_pause && m_blurFade < 0.01)
    {
        m_blurFade += 0.00005;
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastMove).count() >= m_movePeriod)
    {
        addElements();
        moveElements();
        checkEndGame();
        m_lastMove = std::chrono::system_clock::now();
    }

    if ((m_gameState == game_state::RUNNING) && (! m_pause))
    {
        collisionsTest();

        //On test si un personnage n'a plus de vie
        for (unsigned int i=0; i<m_characters.size(); i++)
        {
            if (m_characters[i].second->getLife() == 0 && m_characters[i].second->getState() != character_state::DYING)
            {
                m_characters[i].second->setState(character_state::DYING);
                m_app->getSound().playSound("crash.wav");
            }
        }

        //On augmente la vitesse
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-m_lastAcceleration).count() >= ACCELERATION_PERIOD)
        {
            setSpeedPeriod(--m_movePeriod);
            m_lastAcceleration = std::chrono::system_clock::now();
        }
    } else if (m_gameState == game_state::INTRO) {
        // On positionne tous les personnages à leur position de départ
        for (unsigned int i=0; i<m_characters.size(); i++)
        {
            m_characters[i].second->setPosition(100, 100 + (i*70));
        }
    }
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

int Game::getGameState() const
{
    return m_gameState;
}

int Game::getGameMode() const
{
    return m_gameMode;
}

void Game::setGameState(int state)
{
    m_gameState = state;
    switch (m_gameState)
    {
    case game_state::INTRO:
        Menu::refreshPageContent(this, menuPage::INTRO_GAME);
        break;
    case game_state::RUNNING:
        Menu::refreshPageContent(this, menuPage::ESCAPE_MENU);
        break;
    default:
        break;
    }

}

std::string Game::getClassName() const
{
    return "Game";
}

Player *Game::getPlayer()
{
    return m_player;
}

void Game::setGameMode(int mode)
{
    m_gameMode = mode;
}

void Game::setPause(bool a)
{
    m_pause = a;
    if (m_pause)
    {
        getApp()->getMenuModel().refreshPageContent(this, menuPage::PAUSE);
    } else {
        m_blurFade = 0;
        getApp()->getMenuModel().refreshPageContent(this, menuPage::ESCAPE_MENU);
    }
}

bool Game::isPause() const
{
    return m_pause;
}

float Game::getBlurFade() const
{
    return m_blurFade;
}

void Game::resetGame()
{
    m_pause = 0;
    m_blurFade = 0;
    m_distance = 0;
    m_nextPatternAt = 0;
    setSpeedPeriod(STARTSPEEDPERIODGAME);
    clearAll();
    setGameState(game_state::INTRO);
    GameCharacter *gc = new GameCharacter{100, 0, 100, 50, 0, 0, m_player};
    gc->setId(character_id::PLAYER1);
    m_characters.push_back(std::make_pair(1, gc));
    Image *b1 = new Image{0, 0, MODEL_SIZE_W, MODEL_SIZE_H, "FOND2.png", 1, 0.5, 1, 0};
    Image *b2 = new Image{0, 0, MODEL_SIZE_W, MODEL_SIZE_H, "FOND1.png", 2, 1.0, 1, 0};
    m_images.push_back(std::make_pair(1, b1));
    m_images.push_back(std::make_pair(1, b2));
}

void Game::addElements()
{
    srand(time(nullptr));
    if ((m_gameState == game_state::RUNNING) && (! m_pause))
    {
        //On créé des nouveaux obstacles et bonus en appelant un pattern aléatoire
        if (m_distance > m_nextPatternAt)
        {
            int ran = rand()% m_patternsList.size();
            m_patternsList[ran].addElementsToModel(this);
            m_nextPatternAt = m_distance + m_patternsList[ran].getWidth();
        }

        //On ajoute la distance
        m_distance += PIXELPERBACKGROUNDMOVE;
        for (unsigned int i = 0; i<m_characters.size(); i++)
        {
            if (m_characters[i].second->getState() != DYING)
            {
                m_characters[i].second->addScore(1);
            }
        }
    }
}

void Game::moveElements()
{
    if (!m_pause)
    {
        //On bouge les backgrounds
        for (unsigned int i = 0; i<m_images.size(); i++)
        {
            m_images[i].second->move();
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
    }
    GameCharacter *player1 = getCharacterById(character_id::PLAYER1);
    if (player1 != nullptr)
    {
        float pitch;
        if (player1->getMovement().second != 0.0)
        {
            pitch = 1.0 - (float) player1->getMovement().second/(float)CHARACTER_MAX_SPEED/4.0 ;
        } else {
            pitch = 1.0;
        }
        m_app->getSound().setCharacterSoundPitch(pitch);
    }
}

void Game::collisionsTest()
{
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

    GameCharacter *player1 = getCharacterById(character_id::PLAYER1);
    //Test des collisions avec les obstacles
    std::vector<std::pair<bool, Obstacle *> >::iterator obstacle = m_obstacles.begin();
    while (obstacle != m_obstacles.end())
    {
        bool increment = true;
        if (player1 != nullptr)
        {
            if (obstacle->second->collision(player1))
            {
                if (obstacle->second->getState() != obstacle_state::EXPLODE)
                {
                    player1->removeLife(obstacle->second->getDammage());
                }
                if (obstacle->second->getType() == obstacle_type::MINE)
                {
                    obstacle->second->setState(obstacle_state::EXPLODE);
                    m_app->getSound().playSound("explosion.wav");
                } else {
                    m_deletedElements.push_back(obstacle->second);
                    m_obstacles.erase(obstacle);
                    increment = false;
                }
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
        if (player1 != nullptr)
        {
            if (bonus->second->collision(player1))      //Si il y a collision avec le personnage 1
            {
                switch (bonus->second->getType())               //Action différente suivant le type de bonus
                {
                case bonus_type::PIECE:
                    m_app->getSound().playSound("coin.wav");
                    player1->addScore(1000);
                    break;
                case bonus_type::SOINS:
                    player1->addLife(10);
                    break;
                case bonus_type::INVINSIBLE:
                    player1->addLife(10);
                    break;
                default:
                    break;
                }
                m_deletedElements.push_back(bonus->second);     //on supprime le bonus
                m_bonus.erase(bonus);
                increment = false;
            }
        }
        if (bonus->second->getPosition().first < -bonus->second->getSize().first)   // Si le bonus sort de l'écran à gauche, on le supprime
        {
            m_deletedElements.push_back(bonus->second);
            m_bonus.erase(bonus);
            increment = false;
        }
        if (increment)                  //Si on a supprimé aucun bonus, on passe au suivant sinon pas besoin car les autres se sont trouvés décalés sur la position actuelle
        {
            ++bonus;
        }
    }
}

GameCharacter *Game::getCharacterById(unsigned int id)
{
    std::vector<std::pair<bool, GameCharacter*> >::iterator player = m_characters.begin();
    while (player != m_characters.end() && player->second->getId() != id)
    {
        ++player;
    }
    if (player != m_characters.end())
    {
        return player->second;
    } else {
        return nullptr;
    }
}

void Game::checkEndGame()
{
    bool allDead = true;
    std::vector<std::pair<bool, GameCharacter*> >::iterator character = m_characters.begin();
    while (allDead && character != m_characters.end())
    {
        if (character->second->getState() != character_state::DEAD)
        {
            allDead = false;
        }
        ++character;
    }
    if (allDead)
    {
        m_app->getMenuModel().setPage(menuPage::GAME_ENDED);
    }
}
