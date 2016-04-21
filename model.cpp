#include "model.h"

Model::Model(float width, float height): m_size{width, height}, m_characters{}, m_backgrounds{}, m_obstacles{}, m_bonus{}, m_newElements{}, m_deletedElements{}, m_cursorPosition{}
{

}

std::vector<const Element*> &Model::getDeletedElements()
{
    return m_deletedElements;
}

std::vector<const Element*> &Model::getNewElements()
{
    return m_newElements;
}

std::vector<GameCharacter*> &Model::getCharacters()
{
    return m_characters;
}

std::vector<Background*> &Model::getBackgrounds()
{
    return m_backgrounds;
}

std::vector<Obstacle*> &Model::getObstacles()
{
    return m_obstacles;
}

std::vector<Bonus*> &Model::getBonus()
{
    return m_bonus;
}

std::pair<float, float> Model::getSize() const
{
    return m_size;
}

void Model::setCursorPosition(int x, int y)
{
    m_cursorPosition.first = x;
    m_cursorPosition.second = y;
}
