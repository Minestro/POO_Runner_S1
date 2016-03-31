#include "game.h"

Game::Game()
{
    m_size = std::pair<int, int>{GAME_SIZE_W, GAME_SIZE_H};
    m_newElements.push_back(new GameCharacter{0, 0, 20, 20, 0, 0});
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
