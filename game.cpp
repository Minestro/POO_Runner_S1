#include "game.h"

Game::Game()
{
    m_size = std::pair<int, int>{GAME_SIZE_W, GAME_SIZE_H};
    m_newElements.push_back(new Element{0, 0, 1280, 720, 1, 1});
    m_newElements.push_back(new Element{0, 0, 1920, 1080, 0, 0});
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
