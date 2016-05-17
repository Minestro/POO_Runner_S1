#ifndef OBSTACLESBONUSPATTERN_H
#define OBSTACLESBONUSPATTERN_H
#define TIXML_USE_STL

#include <iostream>
#include "model.h"
#include "TinyXml2/tinyxml2.h"



class ElementsList
{
private:
    unsigned int m_id;
    unsigned int m_width;
    std::vector<Bonus> m_bonusList;
    std::vector<Obstacle> m_obstaclesList;
    std::vector<Image> m_imagesList;
    std::vector<Text> m_textsList;

    int loadBonus(const tinyxml2::XMLElement &bonus);
    int loadObstacles(const tinyxml2::XMLElement &obstacle);
    int loadImages(const tinyxml2::XMLElement &image);
    int loadText(const tinyxml2::XMLElement &text);
public:
    ElementsList(unsigned int id);
    int loadFromFile(const tinyxml2::XMLDocument &file);
    void addElementsToModel(Model *model) const;
    unsigned int getWidth() const;
    unsigned int getId() const;
};

#endif // OBSTACLESBONUSPATTERN_H
