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

void ElementsList::loadFromFile(const XMLDocument &file)
{
    m_obstaclesList.clear();
    m_bonusList.clear();

    int returnCode;
    const XMLElement *patternsList = file.FirstChild()->FirstChildElement("Pattern");
    if (patternsList == nullptr)
    {
        throw XMLError(XML_ERROR_PARSING_ELEMENT);
    }
    int patternIdRead;
    do
    {
        returnCode = patternsList->QueryIntAttribute("id", &patternIdRead);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError(returnCode);
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
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        int widthRead;
        returnCode = patternsList->FirstChildElement("Width")->QueryIntText(&widthRead);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError (returnCode);
        }
        m_width = widthRead;

        const XMLElement *bonusEl = patternsList->FirstChildElement("Bonus");
        do
        {
            if (bonusEl != nullptr)
            {
                loadBonus(*bonusEl);
                bonusEl = bonusEl->NextSiblingElement("Bonus");
            }
        }
        while (bonusEl != nullptr);

        const XMLElement *obstacleEl = patternsList->FirstChildElement("Obstacle");
        do
        {
            if (obstacleEl != nullptr)
            {
                loadObstacles(*obstacleEl);
                obstacleEl = obstacleEl->NextSiblingElement("Obstacle");
            }
        }
        while (obstacleEl != nullptr);

        const XMLElement *imageEl = patternsList->FirstChildElement("Image");
        do
        {
            if (imageEl != nullptr)
            {
                loadImages(*imageEl);
                imageEl = imageEl->NextSiblingElement("Image");
            }
        }
        while (imageEl != nullptr);

        const XMLElement *textEl = patternsList->FirstChildElement("Text");
        do
        {
            if (textEl != nullptr)
            {
                loadText(*textEl);
                textEl = textEl->NextSiblingElement("Text");
            }
        }
        while (textEl != nullptr);
    } else {
        throw XMLError(XML_ERROR_FILE_READ_ERROR);
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

    VarToNodeName e;

    e.intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    e.floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    e.floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    e.floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    e.floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    e.floatAttributeToTagName.push_back(std::make_pair(&mR, "RotateMovement"));
    e.floatAttributeToTagName.push_back(std::make_pair(&r, "RotateAngle"));

    parseElementsText(e, bonus);

    m_bonusList.push_back(Bonus{x + MODEL_SIZE_W, y, width, height, r, -PIXELPERBACKGROUNDMOVE, 0.0f, mR, 0, type});
    return XML_SUCCESS;
}

int ElementsList::loadObstacles(const XMLElement &obstacle)
{
    float width;
    float height;
    float x;
    float y;
    int type;
    int dammage;
    float mR;
    float r;

    VarToNodeName e;

    e.intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    e.intAttributeToTagName.push_back(std::make_pair(&dammage, "Dammage"));
    e.floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    e.floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    e.floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    e.floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    e.floatAttributeToTagName.push_back(std::make_pair(&mR, "RotateMovement"));
    e.floatAttributeToTagName.push_back(std::make_pair(&r, "RotateAngle"));

    parseElementsText(e, obstacle);

    m_obstaclesList.push_back(Obstacle{x + MODEL_SIZE_W, y, width, height, r, -PIXELPERBACKGROUNDMOVE, 0.0f, mR, 0, (unsigned int)dammage, type});
    return XML_SUCCESS;
}

int ElementsList::loadImages(const XMLElement &image)
{
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

    VarToNodeName e;

    e.intAttributeToTagName.push_back(std::make_pair(&zIndex, "ZIndex"));
    e.intAttributeToTagName.push_back(std::make_pair(&movePeriod, "MovePeriod"));
    e.intAttributeToTagName.push_back(std::make_pair(&id, "ID"));
    e.floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    e.floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    e.floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    e.floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    e.floatAttributeToTagName.push_back(std::make_pair(&coefSpeed, "CoefSpeed"));
    e.boolAttributeToTagName.push_back(std::make_pair(&isSliding, "IsSliding"));
    e.stringAttributeToTagName.push_back(std::make_pair(&fileName, "FileName"));

    parseElementsText(e, image);

    m_imagesList.push_back(Image{x, y, width, height, fileName, zIndex, coefSpeed, isSliding, movePeriod});
    return XML_SUCCESS;
}

int ElementsList::loadText(const XMLElement &text)
{
    float width;
    float height;
    float x;
    float y;
    float rotateAngle;
    std::string textB;
    std::string font;
    unsigned int fontSize;
    ColorRGBA color;
    int textEffect;
    unsigned int effectPeriod;
    bool isAutoRescale;
    bool isLineBreacker;

    VarToNodeName e;

    e.floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    e.floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    e.floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    e.floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    e.floatAttributeToTagName.push_back(std::make_pair(&rotateAngle, "RotateAngle"));
    e.uintAttributeToTagName.push_back(std::make_pair(&fontSize, "FontSize"));
    e.intAttributeToTagName.push_back(std::make_pair(&textEffect, "TextEffect"));
    e.uintAttributeToTagName.push_back(std::make_pair(&effectPeriod, "EffectPeriod"));
    e.boolAttributeToTagName.push_back(std::make_pair(&isAutoRescale, "IsAutoRescale"));
    e.boolAttributeToTagName.push_back(std::make_pair(&isLineBreacker, "IsLineBreack"));
    e.stringAttributeToTagName.push_back(std::make_pair(&textB, "String"));
    e.stringAttributeToTagName.push_back(std::make_pair(&font, "Font"));
    e.colorAttributeToTagName.push_back(std::make_pair(&color, "Color"));

    parseElementsText(e, text);

    m_textsList.push_back(Text{x, y, width, height, rotateAngle, textB, fontSize, font, color, textEffect, effectPeriod, isAutoRescale, isLineBreacker});
    return XML_SUCCESS;
}

void ElementsList::parseElementsText(const VarToNodeName &e, const XMLElement &node) const
{
    int returnCode;
    for (unsigned int i=0; i<e.floatAttributeToTagName.size(); i++)
    {
        if (node.FirstChildElement(e.floatAttributeToTagName[i].second.c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        returnCode = node.FirstChildElement(e.floatAttributeToTagName[i].second.c_str())->QueryFloatText(e.floatAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError (returnCode);
        }
    }

    for (unsigned int i=0; i<e.intAttributeToTagName.size(); i++)
    {
        if (node.FirstChildElement(e.intAttributeToTagName[i].second.c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        returnCode = node.FirstChildElement(e.intAttributeToTagName[i].second.c_str())->QueryIntText(e.intAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError (returnCode);
        }
    }

    for (unsigned int i=0; i<e.uintAttributeToTagName.size(); i++)
    {
        if (node.FirstChildElement(e.uintAttributeToTagName[i].second.c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        returnCode = node.FirstChildElement(e.uintAttributeToTagName[i].second.c_str())->QueryUnsignedText(e.uintAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError (returnCode);
        }
    }

    for (unsigned int i=0; i<e.boolAttributeToTagName.size(); i++)
    {
        if (node.FirstChildElement(e.boolAttributeToTagName[i].second.c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        returnCode = node.FirstChildElement(e.boolAttributeToTagName[i].second.c_str())->QueryBoolText(e.boolAttributeToTagName[i].first);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError (returnCode);
        }
    }

    for (unsigned int i=0; i<e.stringAttributeToTagName.size(); i++)
    {
        if (node.FirstChildElement(e.stringAttributeToTagName[i].second.c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        *e.stringAttributeToTagName[i].first = node.FirstChildElement(e.stringAttributeToTagName[i].second.c_str())->GetText();
        if (e.stringAttributeToTagName[i].first->size() == 0)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
    }

    for (unsigned int i=0; i<e.colorAttributeToTagName.size(); i++)
    {
        if (node.FirstChildElement(e.colorAttributeToTagName[i].second.c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        std::string colorS = node.FirstChildElement(e.colorAttributeToTagName[i].second.c_str())->GetText();
        if (colorS.size() == 0)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        } else {
            unsigned int pos = 0;
            std::vector<int> posVirgules;
            while (pos != colorS.size())
            {
                if (colorS[pos] == ',')
                {
                    posVirgules.push_back(pos);
                }
                pos++;
            }
            e.colorAttributeToTagName[i].first->r = std::stoi(colorS.substr(0, posVirgules[0]));
            e.colorAttributeToTagName[i].first->g = std::stoi(colorS.substr(posVirgules[0]+1, posVirgules[1]));
            e.colorAttributeToTagName[i].first->b = std::stoi(colorS.substr(posVirgules[1]+1, posVirgules[2]));
            e.colorAttributeToTagName[i].first->a = std::stoi(colorS.substr(posVirgules[2]+1, posVirgules[3]));
        }
    }
}
