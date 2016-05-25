#include "elementslist.h"
#include "app.h"

using namespace runner;
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

    for (unsigned int i = 0; i<m_buttonsList.size(); i++)
    {
        model->getButtons().push_back(std::make_pair(1, new Button{m_buttonsList[i]}));
    }
}

void ElementsList::loadFromFile(const XMLDocument &file, Model *model)
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
                loadText(*textEl, model);
                textEl = textEl->NextSiblingElement("Text");
            }
        }
        while (textEl != nullptr);

        const XMLElement *buttonEl = patternsList->FirstChildElement("Button");
        do
        {
            if (buttonEl != nullptr)
            {
                loadButton(*buttonEl, model);
                buttonEl = buttonEl->NextSiblingElement("Button");
            }
        }
        while (buttonEl != nullptr);
    } else {
        throw XMLError(XML_ERROR_FILE_READ_ERROR);
    }
}

void ElementsList::loadBonus(const XMLElement &bonus)
{
    float width;
    float height;
    float x;
    float y;
    int type;
    float mR;
    float r;
    int id;

    VarToNodeName e;

    e.intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    e.intAttributeToTagName.push_back(std::make_pair(&id, "ID"));
    e.floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    e.floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    e.floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    e.floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    e.floatAttributeToTagName.push_back(std::make_pair(&mR, "RotateMovement"));
    e.floatAttributeToTagName.push_back(std::make_pair(&r, "RotateAngle"));

    parseElementsText(e, bonus);

    Bonus bo{x + MODEL_SIZE_W, y, width, height, r, -PIXELPERBACKGROUNDMOVE, 0.0f, mR, 0, type};
    bo.setId(id);
    m_bonusList.push_back(bo);
}

void ElementsList::loadObstacles(const XMLElement &obstacle)
{
    float width;
    float height;
    float x;
    float y;
    int type;
    int dammage;
    float mR;
    float r;
    int id;

    VarToNodeName e;

    e.intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    e.intAttributeToTagName.push_back(std::make_pair(&dammage, "Dammage"));
    e.intAttributeToTagName.push_back(std::make_pair(&id, "ID"));
    e.floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    e.floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    e.floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    e.floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    e.floatAttributeToTagName.push_back(std::make_pair(&mR, "RotateMovement"));
    e.floatAttributeToTagName.push_back(std::make_pair(&r, "RotateAngle"));

    parseElementsText(e, obstacle);

    Obstacle ob{x + MODEL_SIZE_W, y, width, height, r, -PIXELPERBACKGROUNDMOVE, 0.0f, mR, 0, (unsigned int)dammage, type};
    ob.setId(id);
    m_obstaclesList.push_back(ob);
}

void ElementsList::loadImages(const XMLElement &image)
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

    Image img{x, y, width, height, fileName, zIndex, coefSpeed, isSliding, movePeriod};
    img.setId(id);
    m_imagesList.push_back(img);

}

void ElementsList::loadText(const XMLElement &text, Model *model)
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
    int id;
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
    e.intAttributeToTagName.push_back(std::make_pair(&id, "ID"));
    e.uintAttributeToTagName.push_back(std::make_pair(&effectPeriod, "EffectPeriod"));
    e.boolAttributeToTagName.push_back(std::make_pair(&isAutoRescale, "IsAutoRescale"));
    e.boolAttributeToTagName.push_back(std::make_pair(&isLineBreacker, "IsLineBreack"));
    e.stringAttributeToTagName.push_back(std::make_pair(&textB, "String"));
    e.stringAttributeToTagName.push_back(std::make_pair(&font, "Font"));
    e.colorAttributeToTagName.push_back(std::make_pair(&color, "Color"));

    parseElementsText(e, text);

    Text txt{x, y, width, height, rotateAngle, Text::getMessage(model->getApp()->getSettings().m_lang, textB), fontSize, font, color, textEffect, effectPeriod, isAutoRescale, isLineBreacker};
    txt.setId(id);
    m_textsList.push_back(txt);
}

void ElementsList::loadButton(const XMLElement &button, Model *model)
{
    float width;
    float height;
    float x;
    float y;
    float rotateAngle;
    std::string text;
    int destinationPage;
    int type;
    std::vector<int> actionsList;
    int id;

    VarToNodeName e;

    e.floatAttributeToTagName.push_back(std::make_pair(&width, "SizeWidth"));
    e.floatAttributeToTagName.push_back(std::make_pair(&height, "SizeHeight"));
    e.floatAttributeToTagName.push_back(std::make_pair(&x, "PositionX"));
    e.floatAttributeToTagName.push_back(std::make_pair(&y, "PositionY"));
    e.floatAttributeToTagName.push_back(std::make_pair(&rotateAngle, "RotateAngle"));
    e.intAttributeToTagName.push_back(std::make_pair(&destinationPage, "DestinationPage"));
    e.intAttributeToTagName.push_back(std::make_pair(&id, "ID"));
    e.intAttributeToTagName.push_back(std::make_pair(&type, "Type"));
    e.stringAttributeToTagName.push_back(std::make_pair(&text, "String"));
    e.listIntAttributeToTagName.push_back(std::make_pair(&actionsList, "ActionsList"));

    parseElementsText(e, button);

    Button bt{x, y, width, height, rotateAngle, Text::getMessage(model->getApp()->getSettings().m_lang, text), destinationPage, model, type};
    bt.setId(id);
    for (int a : actionsList)
    {
        bt.addAction(a);
    }
    m_buttonsList.push_back(bt);


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
        bool defaultId = false;
        if (node.FirstChildElement(e.intAttributeToTagName[i].second.c_str()) == nullptr)
        {
            if (e.intAttributeToTagName[i].second == "ID")
            {
                *e.intAttributeToTagName[i].first = 0;
                defaultId = true;
            } else {
                throw XMLError (XML_ERROR_PARSING_ELEMENT);
            }
        }
        if (!defaultId)
        {
            returnCode = node.FirstChildElement(e.intAttributeToTagName[i].second.c_str())->QueryIntText(e.intAttributeToTagName[i].first);
            if (returnCode != XML_SUCCESS)
            {
                throw XMLError (returnCode);
            }
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
        const char * content = node.FirstChildElement(e.stringAttributeToTagName[i].second.c_str())->GetText();
        if (content != nullptr)
        {
            *e.stringAttributeToTagName[i].first = content;
        } else {
            *e.stringAttributeToTagName[i].first = "";
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
            if (posVirgules.size() == 3)
            {
                e.colorAttributeToTagName[i].first->r = std::stoi(colorS.substr(0, posVirgules[0]));
                e.colorAttributeToTagName[i].first->g = std::stoi(colorS.substr(posVirgules[0]+1, posVirgules[1]-posVirgules[0]-1));
                e.colorAttributeToTagName[i].first->b = std::stoi(colorS.substr(posVirgules[1]+1, posVirgules[2]-posVirgules[1]-1));
                e.colorAttributeToTagName[i].first->a = std::stoi(colorS.substr(posVirgules[2]+1));
            } else {
                throw XMLError(XML_ERROR_PARSING_ELEMENT);
            }
        }
    }

    for (unsigned int i=0; i<e.listIntAttributeToTagName.size(); i++)
    {
        if (node.FirstChildElement(e.listIntAttributeToTagName[i].second.c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        std::string listInt = node.FirstChildElement(e.listIntAttributeToTagName[i].second.c_str())->GetText();
        unsigned int pos = 0;
        unsigned int debut = 0;
        while (pos != listInt.size())
        {
            if (listInt[pos] == ',')
            {
                e.listIntAttributeToTagName[i].first->push_back(std::stoi(listInt.substr(debut, pos-debut)));
                debut = pos+1;
            }
            pos++;
        }
        e.listIntAttributeToTagName[i].first->push_back(std::stoi(listInt.substr(debut)));
        if (e.listIntAttributeToTagName[i].first->size() < 1)
        {
            throw XMLError(XML_ERROR_PARSING_ELEMENT);
        }
    }
}
