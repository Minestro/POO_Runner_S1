#include "elementslist.h"

using namespace tinyxml2;

ElementsList::ElementsList(unsigned int id): m_id{id}, m_width{}, m_bonusList{}, m_obstaclesList{}
{

}

unsigned int ElementsList::getWidth() const
{
    return m_width;
}

unsigned int ElementsList::getId() const
{
    return m_id;
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

    for (unsigned int i = 0; i<m_imagesList.size(); i++)
    {
        model->getImages().push_back(std::make_pair(1, new Image{m_imagesList[i]}));
    }

    for (unsigned int i = 0; i<m_textsList.size(); i++)
    {
        model->getTexts().push_back(std::make_pair(1, new Text{m_textsList[i]}));
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
                textEl = textEl->NextSiblingElement("Text");
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
    int returnCode;
    float width;
    float height;
    float x;
    float y;
    std::string fileName;
    int zIndex;
    float coefSpeed;
    bool isSliding;
    int movePeriod;
    int id;

    std::vector<std::pair<int*, std::string> > intAttributeToTagName;
    std::vector<std::pair<float*, std::string> > floatAttributeToTagName;
    std::vector<std::pair<bool*, std::string> > boolAttributeToTagName;
    std::vector<std::pair<std::string*, std::string> > stringAttributeToTagName;

    intAttributeToTagName.push_back(std::make_pair(&zIndex, "ZIndex"));
    intAttributeToTagName.push_back(std::make_pair(&movePeriod, "MovePeriod"));
    intAttributeToTagName.push_back(std::make_pair(&id, "ID"));
    floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    floatAttributeToTagName.push_back(std::make_pair(&coefSpeed, "CoefSpeed"));
    boolAttributeToTagName.push_back(std::make_pair(&isSliding, "IsSliding"));
    stringAttributeToTagName.push_back(std::make_pair(&fileName, "FileName"));


    for (unsigned int i=0; i<floatAttributeToTagName.size(); i++)
    {
        if (image.FirstChildElement(floatAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = image.FirstChildElement(floatAttributeToTagName[i].second.c_str())->QueryFloatText(floatAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    for (unsigned int i=0; i<intAttributeToTagName.size(); i++)
    {
        if (image.FirstChildElement(intAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = image.FirstChildElement(intAttributeToTagName[i].second.c_str())->QueryIntText(intAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    for (unsigned int i=0; i<boolAttributeToTagName.size(); i++)
    {
        if (image.FirstChildElement(boolAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = image.FirstChildElement(boolAttributeToTagName[i].second.c_str())->QueryBoolText(boolAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    for (unsigned int i=0; i<stringAttributeToTagName.size(); i++)
    {
        if (image.FirstChildElement(stringAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        *stringAttributeToTagName[i].first = image.FirstChildElement(stringAttributeToTagName[i].second.c_str())->GetText();
        if (stringAttributeToTagName[i].first->size() == 0)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
    }

    m_imagesList.push_back(Image{x, y, width, height, fileName, zIndex, coefSpeed, isSliding, movePeriod});
    return XML_SUCCESS;
}

int ElementsList::loadText(const XMLElement &text)
{
    int returnCode;
    float width;
    float height;
    float x;
    float y;
    float rotateAngle;
    std::string textB;
    std::string font;
    int fontSize;
    ColorRGBA color;
    int textEffect;
    int effectPeriod;
    bool isAutoRescale;
    bool isLineBreacker;

    std::vector<std::pair<int*, std::string> > intAttributeToTagName;
    std::vector<std::pair<float*, std::string> > floatAttributeToTagName;
    std::vector<std::pair<bool*, std::string> > boolAttributeToTagName;
    std::vector<std::pair<std::string*, std::string> > stringAttributeToTagName;
    std::vector<std::pair<ColorRGBA*, std::string> > colorAttributeToTagName;

    floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    floatAttributeToTagName.push_back(std::make_pair(&rotateAngle, "RotateAngle"));
    intAttributeToTagName.push_back(std::make_pair(&fontSize, "FontSize"));
    intAttributeToTagName.push_back(std::make_pair(&textEffect, "TextEffect"));
    intAttributeToTagName.push_back(std::make_pair(&effectPeriod, "EffectPeriod"));
    boolAttributeToTagName.push_back(std::make_pair(&isAutoRescale, "IsAutoRescale"));
    boolAttributeToTagName.push_back(std::make_pair(&isLineBreacker, "IsLineBreacker"));
    stringAttributeToTagName.push_back(std::make_pair(&textB, "String"));
    stringAttributeToTagName.push_back(std::make_pair(&font, "Font"));
    colorAttributeToTagName.push_back(std::make_pair(&color, "Color"));


    for (unsigned int i=0; i<floatAttributeToTagName.size(); i++)
    {
        if (text.FirstChildElement(floatAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = text.FirstChildElement(floatAttributeToTagName[i].second.c_str())->QueryFloatText(floatAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    for (unsigned int i=0; i<intAttributeToTagName.size(); i++)
    {
        if (text.FirstChildElement(intAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = text.FirstChildElement(intAttributeToTagName[i].second.c_str())->QueryIntText(intAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    for (unsigned int i=0; i<boolAttributeToTagName.size(); i++)
    {
        if (text.FirstChildElement(boolAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        returnCode = text.FirstChildElement(boolAttributeToTagName[i].second.c_str())->QueryBoolText(boolAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            return returnCode;
        }
    }

    for (unsigned int i=0; i<stringAttributeToTagName.size(); i++)
    {
        if (text.FirstChildElement(stringAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        *stringAttributeToTagName[i].first = text.FirstChildElement(stringAttributeToTagName[i].second.c_str())->GetText();
        if (stringAttributeToTagName[i].first->size() == 0)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
    }

    for (unsigned int i=0; i<colorAttributeToTagName.size(); i++)
    {
        if (text.FirstChildElement(colorAttributeToTagName[i].second.c_str()) == nullptr)
        {
            return XML_ERROR_PARSING_ELEMENT;
        }
        std::string colorS = text.FirstChildElement(colorAttributeToTagName[i].second.c_str())->GetText();
        if (colorS.size() == 0)
        {
            return XML_ERROR_PARSING_ELEMENT;
        } else {
            unsigned int pos = 0;
            std::vector<int> posVirgules;
            while (pos != colorS.size())
            {
                if (colorS[pos] == ',')
                {
                    posVirgules.push_back(pos);
                }
                i++;
            }
            color.r = std::stoi(colorS.substr(0, posVirgules[0]-1));
            color.g = std::stoi(colorS.substr(posVirgules[0]+1, posVirgules[1]-1));
            color.b = std::stoi(colorS.substr(posVirgules[1]+1, posVirgules[2]-1));
            color.a = std::stoi(colorS.substr(posVirgules[2]+1, posVirgules[3]-1));
        }
    }
    m_textsList.push_back(Text{x, y, width, height, rotateAngle, textB, fontSize, font, color, textEffect, effectPeriod, isAutoRescale, isLineBreacker});
    return XML_SUCCESS;
}
