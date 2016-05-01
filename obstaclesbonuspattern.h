#ifndef OBSTACLESBONUSPATTERN_H
#define OBSTACLESBONUSPATTERN_H

#include <iostream>
#include "model.h"

class ObstaclesBonusPattern
{
private:
    unsigned int m_id;
    unsigned int m_width;
    Model *m_model;
    std::vector<Bonus> m_bonusList;
    std::vector<Obstacle> m_obstaclesList;
public:
    ObstaclesBonusPattern() = default;
    ObstaclesBonusPattern(unsigned int id, Model *model);
    void loadFromFile(unsigned int id);
    void addElementsToModel() const;
};

#endif // OBSTACLESBONUSPATTERN_H
