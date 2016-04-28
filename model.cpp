#include "model.h"

Model::Model(float width, float height): m_size{width, height}, m_characters{}, m_backgrounds{}, m_obstacles{}, m_bonus{}, m_texts{}, m_deletedElements{}, m_cursorPosition{}
{

}

std::vector<const Element*> &Model::getDeletedElements()
{
    return m_deletedElements;
}

std::vector<std::pair<bool, GameCharacter *> > &Model::getCharacters()
{
    return m_characters;
}

std::vector<std::pair<bool, Background *> > &Model::getBackgrounds()
{
    return m_backgrounds;
}

std::vector<std::pair<bool, Obstacle *> > &Model::getObstacles()
{
    return m_obstacles;
}

std::vector<std::pair<bool, Bonus *> > &Model::getBonus()
{
    return m_bonus;
}

std::vector<std::pair<bool, Button*> > &Model::getButtons()
{
    return m_buttons;
}

std::vector<std::pair<bool, Text*> > &Model::getTexts()
{
    return m_texts;
}

std::pair<float, float> Model::getSize() const
{
    return m_size;
}

std::pair<int, int> Model::getCursorPosition() const
{
    return m_cursorPosition;
}

void Model::setCursorPosition(int x, int y)
{
    m_cursorPosition.first = x;
    m_cursorPosition.second = y;
}
