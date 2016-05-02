#ifndef OBSTACLESBONUSPATTERN_H
#define OBSTACLESBONUSPATTERN_H
#define TIXML_USE_STL

#include <iostream>
#include "model.h"
#include <TinyXml2/tinyxml2.h>


class ObstaclesBonusPattern
{
private:
    unsigned int m_id;
    unsigned int m_width;
    Model *m_model;
    std::vector<Bonus> m_bonusList;
    std::vector<Obstacle> m_obstaclesList;

    int loadBonus(const tinyxml2::XMLElement &bonus);
    int loadObstacles(const tinyxml2::XMLElement &obstacle);
public:
    ObstaclesBonusPattern() = default;
    ObstaclesBonusPattern(unsigned int id, Model *model);
    int loadFromFile(const tinyxml2::XMLDocument &file);
    void addElementsToModel() const;
    unsigned int getWidth() const;
};

#endif // OBSTACLESBONUSPATTERN_H
