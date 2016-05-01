#include "obstaclesbonuspattern.h"

ObstaclesBonusPattern::ObstaclesBonusPattern(unsigned int id, Model *model): m_id{id}, m_width{}, m_model{model}, m_bonusList{}, m_obstaclesList{}
{

}

void ObstaclesBonusPattern::addElementsToModel() const
{
    for (unsigned int i=0; i<m_bonusList.size(); i++)
    {
        m_model->getBonus().push_back(std::make_pair(1, new Bonus{m_bonusList[i]}));
    }

    for (unsigned int i=0; i<m_obstaclesList.size(); i++)
    {
        m_model->getObstacles().push_back(std::make_pair(1, new Obstacle{m_obstaclesList[i]}));
    }
}

void ObstaclesBonusPattern::loadFromFile(unsigned int id)
{
    m_obstaclesList.clear();
    m_bonusList.clear();

}
