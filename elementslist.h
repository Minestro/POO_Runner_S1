#ifndef OBSTACLESBONUSPATTERN_H
#define OBSTACLESBONUSPATTERN_H
#define TIXML_USE_STL

#include <iostream>
#include "model.h"
#include "TinyXml2/tinyxml2.h"

struct VarToNodeName
{
    VarToNodeName() = default;
    std::vector<std::pair<int*, std::string> > intAttributeToTagName;
    std::vector<std::pair<float*, std::string> > floatAttributeToTagName;
    std::vector<std::pair<bool*, std::string> > boolAttributeToTagName;
    std::vector<std::pair<std::string*, std::string> > stringAttributeToTagName;
    std::vector<std::pair<ColorRGBA*, std::string> > colorAttributeToTagName;
    std::vector<std::pair<unsigned int*, std::string> > uintAttributeToTagName;
};

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
    void parseElementsText(const VarToNodeName &e, const tinyxml2::XMLElement &node) const;
public:
    ElementsList(unsigned int id);
    void loadFromFile(const tinyxml2::XMLDocument &file);
    void addElementsToModel(Model *model) const;
    unsigned int getWidth() const;
    unsigned int getId() const;
};

#endif // OBSTACLESBONUSPATTERN_H
