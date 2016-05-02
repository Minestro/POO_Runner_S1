#include "obstaclesbonuspattern.h"

using namespace tinyxml2;

ObstaclesBonusPattern::ObstaclesBonusPattern(unsigned int id, Model *model): m_id{id}, m_width{}, m_model{model}, m_bonusList{}, m_obstaclesList{}
{

}

unsigned int ObstaclesBonusPattern::getWidth() const
{
    return m_width;
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

int ObstaclesBonusPattern::loadFromFile(const XMLDocument &file)
{
    m_obstaclesList.clear();
    m_bonusList.clear();

    int returnCode;
    const XMLElement *patternsList = file.FirstChild()->FirstChildElement("Pattern");
    if (patternsList == nullptr)
    {
        return XML_ERROR_PARSING_ELEMENT;
    }
    int patternIdRead;
    do
    {
        returnCode = patternsList->QueryIntAttribute("id", &patternIdRead);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
        if (patternIdRead != (int)m_id)
        {
            patternsList = patternsList->NextSiblingElement("Pattern");
        }
    } while (patternsList != nullptr && patternIdRead != (int)m_id);
    if (patternIdRead == (int)m_id)
    {
        if (patternsList->FirstChildElement("Width") == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        int widthRead;
        returnCode = patternsList->FirstChildElement("Width")->QueryIntText(&widthRead);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
        m_width = widthRead;

        const XMLElement *bonusEl = patternsList->FirstChildElement("Bonus");
        if (bonusEl == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        do
        {
            if (bonusEl != nullptr)
            {
                returnCode = loadBonus(*bonusEl);
                if (returnCode != XML_SUCCESS)
                {
                    return returnCode;
                }
            }
            bonusEl = bonusEl->NextSiblingElement("Bonus");
        }
        while (bonusEl != nullptr);

        const XMLElement *obstacleEl = patternsList->FirstChildElement("Obstacle");
        if (obstacleEl == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        do
        {
            if (obstacleEl != nullptr)
            {
                returnCode = loadObstacles(*obstacleEl);
                if (returnCode != XML_SUCCESS)
                {
                    return returnCode;
                }
            }
            obstacleEl = obstacleEl->NextSiblingElement("Obstacle");
        }
        while (obstacleEl != nullptr);

        return XML_SUCCESS;
    } else {
        return XML_ERROR_FILE_READ_ERROR;
    }
}

int ObstaclesBonusPattern::loadBonus(const XMLElement &bonus)
{
    float width;
    float height;
    float x;
    float y;
    int type;
    float mR;
    int returnCode;

    std::vector<std::pair<int*, std::string> > intAttributeToTagName;
    std::vector<std::pair<float*, std::string> > floatAttributeToTagName;

    intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    floatAttributeToTagName.push_back(std::make_pair(&mR, "RotateMovement"));

    for (unsigned int i=0; i<floatAttributeToTagName.size(); i++)
    {
        if (bonus.FirstChildElement(floatAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = bonus.FirstChildElement(floatAttributeToTagName[i].second.c_str())->QueryFloatText(floatAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    for (unsigned int i=0; i<intAttributeToTagName.size(); i++)
    {
        if (bonus.FirstChildElement(intAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = bonus.FirstChildElement(intAttributeToTagName[i].second.c_str())->QueryIntText(intAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    m_bonusList.push_back(Bonus{x + GAME_SIZE_W, y, width, height, -PIXELPERBACKGROUNDMOVE, 0.0f, 0, type});
    return XML_SUCCESS;
}

int ObstaclesBonusPattern::loadObstacles(const XMLElement &obstacle)
{
    int returnCode;
    float width;
    float height;
    float x;
    float y;
    int type;
    int dammage;
    float mR;

    std::vector<std::pair<int*, std::string> > intAttributeToTagName;
    std::vector<std::pair<float*, std::string> > floatAttributeToTagName;

    intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    intAttributeToTagName.push_back(std::make_pair(&dammage, "Dammage"));
    floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    floatAttributeToTagName.push_back(std::make_pair(&mR, "RotateMovement"));

    for (unsigned int i=0; i<floatAttributeToTagName.size(); i++)
    {
        if (obstacle.FirstChildElement(floatAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = obstacle.FirstChildElement(floatAttributeToTagName[i].second.c_str())->QueryFloatText(floatAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    for (unsigned int i=0; i<intAttributeToTagName.size(); i++)
    {
        if (obstacle.FirstChildElement(intAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = obstacle.FirstChildElement(intAttributeToTagName[i].second.c_str())->QueryIntText(intAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    m_obstaclesList.push_back(Obstacle{x + GAME_SIZE_W, y, width, height, -PIXELPERBACKGROUNDMOVE, 0.0f, 0, (unsigned int)dammage, type});
    return XML_SUCCESS;
}
