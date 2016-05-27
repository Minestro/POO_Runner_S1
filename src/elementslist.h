/*Copyright (C) 2015 Original code by Jacquot Alexandre - Julien Morgane

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

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
    std::vector<std::pair<std::vector<int>*, std::string> > listIntAttributeToTagName;
};

class ElementsList
{
private:
    unsigned int m_id;
    unsigned int m_width;       //Largeur du pattern utile en jeu pour définir la position du prochain pattern d'obstacles
    std::vector<Bonus> m_bonusList;
    std::vector<Obstacle> m_obstaclesList;
    std::vector<Image> m_imagesList;
    std::vector<runner::Text> m_textsList;
    std::vector<Button> m_buttonsList;

    void loadBonus(const tinyxml2::XMLElement &bonus);
    void loadObstacles(const tinyxml2::XMLElement &obstacle);
    void loadImages(const tinyxml2::XMLElement &image);
    void loadText(const tinyxml2::XMLElement &text, Model *model);
    void loadButton(const tinyxml2::XMLElement &button, Model *model);
    void parseElementsText(const VarToNodeName &e, const tinyxml2::XMLElement &node) const;
public:
    ElementsList(unsigned int id);
    void loadFromFile(const tinyxml2::XMLDocument &file, Model *model);
    void addElementsToModel(Model *model) const;        //Ajout des élements du pattern au modèle pour affichage
    unsigned int getWidth() const;
    unsigned int getId() const;
};

#endif // OBSTACLESBONUSPATTERN_H
