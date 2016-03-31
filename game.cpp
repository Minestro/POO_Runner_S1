#include "game.h"

Game::Game()
{
    m_size = std::pair<int, int>{GAME_SIZE_W, GAME_SIZE_H};
    m_newElements.push_back(new Background{"city.png"});
    this->m_character = new GameCharacter{0, HAUTEUR_SOL, 40, 40, 0, 0};
    m_newElements.push_back(m_character);

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
    m_character->move();
}
