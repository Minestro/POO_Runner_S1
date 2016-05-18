#include "game.h"
#include "app.h"

using namespace tinyxml2;

Game::Game(float width, float height, unsigned int movePeriodMs, App *app): Model::Model{width, height, app}, m_pause{false}, m_gameMode{game_mode::SOLO}, m_lastMove{}, m_lastAcceleration{}, m_movePeriod{movePeriodMs}, m_player{nullptr}, m_distance{0}, m_powerActives{}, m_nextPatternAt{0}, m_blurFade{0.0f}
{
    m_player =  new Player;
    GameCharacter *gc = new GameCharacter{100, 0, 100, 50, 0, 0, m_player};
    gc->setId(character_id::PLAYER1);
    m_characters.push_back(std::make_pair(1, gc));
    Image *b1 = new Image{0, 0, MODEL_SIZE_W, MODEL_SIZE_H, "FOND2.png", 1, 0.5, 1, 0};
    Image *b2 = new Image{0, 0, MODEL_SIZE_W, MODEL_SIZE_H, "FOND1.png", 2, 1.0, 1, 0};
    m_images.push_back(std::make_pair(1, b1));
    m_images.push_back(std::make_pair(1, b2));

    setGameState(game_state::INTRO);
    setSpeedPeriod(m_movePeriod);
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
    delete m_player;
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
        op.loadFromFile(patternsFile, m_app);
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
    srand(time(nullptr));

    std::vector<std::pair<bool, GameCharacter*> >::iterator player1 = m_characters.begin();
    while (player1 != m_characters.end() && player1->second->getId() != character_id::PLAYER1)
    {
        ++player1;
    }

    if (m_pause && m_blurFade < 0.01)
    {
        m_blurFade += 0.00005;
    }

    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastMove).count() >= m_movePeriod)
    {
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

        m_lastMove = std::chrono::system_clock::now();
    }

    if ((m_gameState == game_state::RUNNING) && (! m_pause))
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

        //Test des collisions avec les obstacles
        std::vector<std::pair<bool, Obstacle *> >::iterator obstacle = m_obstacles.begin();
        while (obstacle != m_obstacles.end())
        {
            bool increment = true;
            if (player1 != m_characters.end())
            {
                if (obstacle->second->collision(m_characters[0].second))
                {
                    if (obstacle->second->getState() != obstacle_state::EXPLODE)
                    {
                        m_characters[0].second->removeLife(obstacle->second->getDammage());
                    }
                    if (obstacle->second->getType() == obstacle_type::MINE ||obstacle->second->getType() == obstacle_type::NUAGE ||obstacle->second->getType() == obstacle_type::BARRE )
                    {
                        obstacle->second->setState(obstacle_state::EXPLODE);
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
            if (player1 != m_characters.end())
            {
                if (bonus->second->collision(m_characters[0].second))      //Si il y a collision avec le personnage 1
                {
                    switch (bonus->second->getType())               //Action différente suivant le type de bonus
                    {
                    case bonus_type::PIECE:
                        m_characters[0].second->addScore(1000);
                        break;
                    case bonus_type::SOINS:
                        m_characters[0].second->addLife(10);
                        break;
                    case bonus_type::INVINSIBLE:
                        m_characters[0].second->addLife(10);
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
    } else if (m_gameState == game_state::INTRO)
    {

        for (unsigned int i=0; i<m_characters.size(); i++)
        {
            m_characters[i].second->setPosition(100, 100 + (i*70));
        }
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
        if (searchElementById(GAMEINTROTEXTID) == nullptr)
        {
            Text *text = new Text{0, 600, MODEL_SIZE_W, 50, 0, "Appuyez sur une touche pour lancer l'avion", 20, "score.ttf", ColorRGBA::White,text_effect::BREATH, 20, 1, 0};
            m_texts.push_back(std::make_pair(1, text));

            text->setId(GAMEINTROTEXTID);
        }
        break;
    case game_state::RUNNING:
        deleteElement(GAMEINTROTEXTID);
        break;
    default:
        break;
    }

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
    setGameState(game_state::INTRO);
    setSpeedPeriod(STARTSPEEDPERIODGAME);
    clearAll();
    m_player =  new Player;
    GameCharacter *gc = new GameCharacter{100, 0, 100, 50, 0, 0, m_player};
    gc->setId(character_id::PLAYER1);
    m_characters.push_back(std::make_pair(1, gc));
    Image *b1 = new Image{0, 0, MODEL_SIZE_W, MODEL_SIZE_H, "FOND2.png", 1, 0.5, 1, 0};
    Image *b2 = new Image{0, 0, MODEL_SIZE_W, MODEL_SIZE_H, "FOND1.png", 2, 1.0, 1, 0};
    m_images.push_back(std::make_pair(1, b1));
    m_images.push_back(std::make_pair(1, b2));
}
