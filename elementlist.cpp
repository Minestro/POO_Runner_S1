#include "elementslist.h"

using namespace tinyxml2;

ElementsList::ElementsList(unsigned int id): m_id{id}, m_width{}, m_bonusList{}, m_obstaclesList{}
{

}

unsigned int ElementsList::getWidth() const
{
    return m_width;
}

void ElementsList::addElementsToModel(Model *model) const
{
    for (unsigned int i=0; i<m_bonusList.size(); i++)
    {
        model->getBonus().push_back(std::make_pair(1, new Bonus{m_bonusList[i]}));
    }

    for (unsigned int i=0; i<m_obstaclesList.size(); i++)
    {
        model->getObstacles().push_back(std::make_pair(1, new Obstacle{m_obstaclesList[i]}));
    }
}

int ElementsList::loadFromFile(const XMLDocument &file)
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
        do
        {
            if (bonusEl != nullptr)
            {
                returnCode = loadBonus(*bonusEl);
                if (returnCode != XML_SUCCESS)
                {
                    return returnCode;
                }
                bonusEl = bonusEl->NextSiblingElement("Bonus");
            }
        }
        while (bonusEl != nullptr);

        const XMLElement *obstacleEl = patternsList->FirstChildElement("Obstacle");
        do
        {
            if (obstacleEl != nullptr)
            {
                returnCode = loadObstacles(*obstacleEl);
                if (returnCode != XML_SUCCESS)
                {
                    return returnCode;
                }
                obstacleEl = obstacleEl->NextSiblingElement("Obstacle");
            }
        }
        while (obstacleEl != nullptr);

        const XMLElement *imageEl = patternsList->FirstChildElement("Image");
        do
        {
            if (imageEl != nullptr)
            {
                returnCode = loadImages(*imageEl);
                if (returnCode != XML_SUCCESS)
                {
                    return returnCode;
                }
                imageEl = imageEl->NextSiblingElement("Image");
            }
        }
        while (imageEl != nullptr);

        const XMLElement *textEl = patternsList->FirstChildElement("Text");
        do
        {
            if (textEl != nullptr)
            {
                returnCode = loadText(*textEl);
                if (returnCode != XML_SUCCESS)
                {
                    return returnCode;
                }
                loadText = textEl->NextSiblingElement("Text");
            }
        }
        while (textEl != nullptr);

        return XML_SUCCESS;
    } else {
        return XML_ERROR_FILE_READ_ERROR;
    }
}

int ElementsList::loadBonus(const XMLElement &bonus)
{
    float width;
    float height;
    float x;
    float y;
    int type;
    float mR;
    float r;
    int returnCode;

    std::vector<std::pair<int*, std::string> > intAttributeToTagName;
    std::vector<std::pair<float*, std::string> > floatAttributeToTagName;

    intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    floatAttributeToTagName.push_back(std::make_pair(&mR, "RotateMovement"));
    floatAttributeToTagName.push_back(std::make_pair(&r, "RotateAngle"));

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

    m_bonusList.push_back(Bonus{x + MODEL_SIZE_W, y, width, height, r, -PIXELPERBACKGROUNDMOVE, 0.0f, mR, 0, type});
    return XML_SUCCESS;
}

int ElementsList::loadObstacles(const XMLElement &obstacle)
{
    int returnCode;
    float width;
    float height;
    float x;
    float y;
    int type;
    int dammage;
    float mR;
    float r;

    std::vector<std::pair<int*, std::string> > intAttributeToTagName;
    std::vector<std::pair<float*, std::string> > floatAttributeToTagName;

    intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    intAttributeToTagName.push_back(std::make_pair(&dammage, "Dammage"));
    floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    floatAttributeToTagName.push_back(std::make_pair(&mR, "RotateMovement"));
    floatAttributeToTagName.push_back(std::make_pair(&r, "RotateAngle"));

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

    m_obstaclesList.push_back(Obstacle{x + MODEL_SIZE_W, y, width, height, r, -PIXELPERBACKGROUNDMOVE, 0.0f, mR, 0, (unsigned int)dammage, type});
    return XML_SUCCESS;
}

int ElementsList::loadImages(const XMLElement &image)
{
    float width;
    float height;
    float x;
    float y;
    int zIndex;
    float coefSpeed;
    bool isSliding;
    int movePeriod;
    std::string id;

    std::vector<std::pair<int*, std::string> > intAttributeToTagName;
    std::vector<std::pair<float*, std::string> > floatAttributeToTagName;
    std::vector<std::pair<bool*, std::string> > boolAttributeToTagName;
    std::vector<std::pair<std::string*, std::string> > stringAttributeToTagName;

    intAttributeToTagName.push_back(std::make_pair(&zIndex, "ZIndex"));
    floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));

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

    m_bonusList.push_back(Bonus{x + MODEL_SIZE_W, y, width, height, r, -PIXELPERBACKGROUNDMOVE, 0.0f, mR, 0, type});
    return XML_SUCCESS;
}

int ElementsList::loadText(const XMLElement &text)
{

}
