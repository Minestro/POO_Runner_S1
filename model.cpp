#include "model.h"

Model::Model(float width, float height): m_size{width, height}, m_characters{}, m_images{}, m_obstacles{}, m_bonus{}, m_texts{}, m_deletedElements{}, m_cursorPosition{}
{
    clearAll();
    for (unsigned int i=0; i<m_deletedElements.size(); i++)
    {
        delete m_deletedElements[i];
    }
}

std::vector<const Element*> &Model::getDeletedElements()
{
    return m_deletedElements;
}

std::vector<std::pair<bool, GameCharacter *> > &Model::getCharacters()
{
    return m_characters;
}

std::vector<std::pair<bool, Image *> > &Model::getImages()
{
    return m_images;
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

void Model::clearAll()
{
    for (unsigned int i = 0; i<m_images.size(); i++)
    {
        m_deletedElements.push_back(m_images[i].second);
    }
    m_images.clear();
    for (unsigned int i = 0; i<m_bonus.size(); i++)
    {
        m_deletedElements.push_back(m_bonus[i].second);
    }
    m_bonus.clear();
    for (unsigned int i = 0; i<m_buttons.size(); i++)
    {
        m_deletedElements.push_back(m_buttons[i].second);
    }
    m_buttons.clear();
    for (unsigned int i = 0; i<m_characters.size(); i++)
    {
        m_deletedElements.push_back(m_characters[i].second);
    }
    m_characters.clear();
    for (unsigned int i = 0; i<m_obstacles.size(); i++)
    {
        m_deletedElements.push_back(m_obstacles[i].second);
    }
    m_obstacles.clear();
    for (unsigned int i = 0; i<m_texts.size(); i++)
    {
        m_deletedElements.push_back(m_texts[i].second);
    }
    m_texts.clear();
}
