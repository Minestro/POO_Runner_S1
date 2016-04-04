#include "game.h"

Game::Game(): m_score{0}, m_speedPeriod{100}, m_lastNextStepCall{}, m_beginGameTime{}, m_pauseTime{0}, m_size{std::pair<int, int>{GAME_SIZE_W, GAME_SIZE_H}}, m_backgrounds{}, m_obstacles{}, m_bonus{}, m_newElements{}, m_deletedElements{}
{
    this->m_backgrounds.push_back(new Background{"city.png", 1, 0});
    this->m_character = new GameCharacter{0, HAUTEUR_SOL, 40, 40, 0, 0};
    m_newElements.push_back(m_character);
    m_backgrounds::iterator iterator = m_backgrounds.begin();
    while (iterator != m_backgrounds.end())
    {
        m_newElements.push_back(*iterator);
    }
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
    m_backgrounds::iterator iterator = m_backgrounds.begin();
    while (iterator != m_backgrounds.end())
    {
        (**iterator).slide();
    }
    m_character->move();
}
