#include "game.h"

Game::Game()
{
    m_newElements.push_back(new Element{1, 0, 0, 1920, 1080, 1});
    m_newElements.push_back(new Element{0, 0, 0, 1920, 1080, 0});
}

std::vector<const Element*> &Game::getDeletedElements()
{
    return m_deletedElements;
}

std::vector<const Element*> &Game::getNewElements()
{
    return m_newElements;
}
