#include "game.h"

Game::Game(): m_score{0}, m_speedPeriod{100}, m_lastNextStepCall{}, m_beginGameTime{}, m_pauseTime{0}, m_size{std::pair<int, int>{GAME_SIZE_W, GAME_SIZE_H}}, m_backgrounds{}, m_obstacles{}, m_bonus{}, m_newElements{}, m_deletedElements{}
{
    this->m_character = new GameCharacter{0, HAUTEUR_SOL, 40, 40, 0, 0};
    m_newElements.push_back(m_character);
    Background *b = new Background{"city_2.png", 0, 1, 0};
    Background *b2 = new Background{"city_1.png", 1, 1, 0};
    m_newElements.push_back(b);
    m_backgrounds.push_back(b);
    m_newElements.push_back(b2);
    m_backgrounds.push_back(b2);
}

Game::~Game()
{
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

void Game::nextStep()
{
    std::vector<Background *>::iterator iterator = m_backgrounds.begin();
    while (iterator != m_backgrounds.end())
    {
        (**iterator).slide();
        ++iterator;
    }
    m_character->move();
}
