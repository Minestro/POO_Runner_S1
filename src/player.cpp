#include "player.h"

using namespace tinyxml2;

Player::Player(): m_bestScore{0}, m_nickName{"Guest"}, m_money{0}, m_id{NB_MAX_SAVES+1}, m_powerUpgrades{}
{
    for (unsigned int i = 0; i<power_list::NB_POWER; i++)
    {
        m_powerUpgrades[i] = (DEFAULT_UPGRADE_SEC * 1000);
    }
}

Player::Player(unsigned int i): m_bestScore{0}, m_nickName{"Guest"}, m_money{0}, m_id{i}, m_powerUpgrades{}
{
    for (unsigned int i = 0; i<power_list::NB_POWER; i++)
    {
        m_powerUpgrades[i] = (DEFAULT_UPGRADE_SEC * 1000);
    }
    try
    {
        if (Player::isActive(i))
        {
            loadSaveFromFile();
        }
    }
    catch (XMLError e)
    {
        std::cout << "Erreur lors du chargement du profil. Code Erreur : " << std::to_string(e) << std::endl;
        m_bestScore = 0;
        m_nickName = "Guest";
        m_money = 0;
        for (unsigned int i = 0; i<power_list::NB_POWER; i++)
        {
            m_powerUpgrades[i] = (DEFAULT_UPGRADE_SEC * 1000);
        }
    }
}

std::string Player::getName() const
{
    return m_nickName;
}

void Player::setNickName(std::string name)
{
    m_nickName = name;
}

unsigned int Player::getBestScore() const
{
    return m_bestScore;
}

unsigned int Player::getId() const
{
    return m_id;
}

void Player::setBestScore(unsigned int score)
{
    m_bestScore = score;
}

void Player::saveProfile() const
{
    int returnCode;
    XMLDocument saveFile;
    XMLElement *el = Player::getNodePlayerId(m_id, saveFile);
    if (el->FirstChildElement("Active") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    el->FirstChildElement("Active")->SetText(1);
    if (el->FirstChildElement("NickName") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    el->FirstChildElement("NickName")->SetText(m_nickName.c_str());
    for (unsigned int i=0; i<power_list::NB_POWER; i++)
    {
        if (el->FirstChildElement(std::string("Upgrade" + std::to_string(i+1)).c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        el->FirstChildElement(std::string("Upgrade" + std::to_string(i+1)).c_str())->SetText(m_powerUpgrades[i]);
    }
    if (el->FirstChildElement("BestScore") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    el->FirstChildElement("BestScore")->SetText(m_bestScore);
    if (el->FirstChildElement("Money") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    el->FirstChildElement("Money")->SetText(m_money);
    returnCode = saveFile.SaveFile(SAVE_FILE.c_str());
    if (returnCode != XML_SUCCESS)
    {
        throw XMLError(returnCode);
    }
}

void Player::loadSaveFromFile()
{
    int returnCode;
    XMLDocument saveFile;
    const XMLElement *el = Player::getConstNodePlayerId(m_id, saveFile);
    if (!isActive(m_id))
    {
        throw XMLError (XML_ERROR_IDENTIFYING_TAG);
    } else {
        if (el->FirstChildElement("NickName") == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        const char * nickName;
        nickName = el->FirstChildElement("NickName")->GetText();
        if (nickName == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        m_nickName = nickName;
        unsigned int upgradeTime;
        for (unsigned int i=0; i<power_list::NB_POWER; i++)
        {
            if (el->FirstChildElement(std::string("Upgrade" + std::to_string(i+1)).c_str()) == nullptr)
            {
                throw XMLError (XML_ERROR_PARSING_ELEMENT);
            }
            returnCode = el->FirstChildElement(std::string("Upgrade" + std::to_string(i+1)).c_str())->QueryUnsignedText(&upgradeTime);
            if (returnCode != XML_SUCCESS)
            {
                throw XMLError (returnCode);
            }
            m_powerUpgrades[i] = upgradeTime;
        }
        if (el->FirstChildElement("BestScore") == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        unsigned int bestScore;
        returnCode = el->FirstChildElement("BestScore")->QueryUnsignedText(&bestScore);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError (returnCode);
        }
        m_bestScore = bestScore;
        if (el->FirstChildElement("Money") == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        unsigned int money;
        returnCode = el->FirstChildElement("Money")->QueryUnsignedText(&money);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError (returnCode);
        }
        m_money = money;
    }
}

bool Player::buy(unsigned int upgradeId)
{
    if (upgradeId > power_list::NB_POWER-1)
    {
        return false;
    } else if ((m_money - UPGRADE_COST > 0) && (m_powerUpgrades[upgradeId] < MAX_UPGRADE_SEC * 1000))
    {
        m_money -= UPGRADE_COST;
        m_powerUpgrades[upgradeId] += (SEC_PER_UPGRADE * 1000);
        return true;
    } else {
        return false;
    }
}

void Player::addMoney(unsigned int money)
{
    m_money += money;
}

unsigned int Player::getMoney() const
{
    return m_money;
}

void Player::eraseProfil(unsigned int i)
{
    int returnCode;
    XMLDocument saveFile;
    XMLElement *el = Player::getNodePlayerId(i, saveFile);
    if (el->FirstChildElement("Active") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    el->FirstChildElement("Active")->SetText(0);
    if (el->FirstChildElement("NickName") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    el->FirstChildElement("NickName")->SetText("");
    for (unsigned int i=0; i<power_list::NB_POWER; i++)
    {
        if (el->FirstChildElement(std::string("Upgrade" + std::to_string(i+1)).c_str()) == nullptr)
        {
            throw XMLError (XML_ERROR_PARSING_ELEMENT);
        }
        el->FirstChildElement(std::string("Upgrade" + std::to_string(i+1)).c_str())->SetText("");
    }
    if (el->FirstChildElement("BestScore") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    el->FirstChildElement("BestScore")->SetText("");
    if (el->FirstChildElement("Money") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    el->FirstChildElement("Money")->SetText("");
    returnCode = saveFile.SaveFile(SAVE_FILE.c_str());
    if (returnCode != XML_SUCCESS)
    {
        throw XMLError(returnCode);
    }
}

bool Player::isActive(unsigned int i)
{
    int returnCode;
    XMLDocument saveFile;
    const XMLElement *el = Player::getConstNodePlayerId(i, saveFile);
    if (el->FirstChildElement("Active") == nullptr)
    {
        throw XMLError (XML_ERROR_PARSING_ELEMENT);
    }
    bool active;
    returnCode = el->FirstChildElement("Active")->QueryBoolText(&active);
    if (returnCode != XML_SUCCESS)
    {
        throw XMLError (returnCode);
    }
    return active;

}

XMLElement *Player::getNodePlayerId(unsigned int id, XMLDocument &saveFile)
{
    int returnCode;
    returnCode = saveFile.LoadFile(SAVE_FILE.c_str());
    if (returnCode != XML_SUCCESS)
    {
        throw XMLError (returnCode);
    }
    XMLNode *pRoot = saveFile.FirstChild();
    if (pRoot == nullptr)
    {
        throw XMLError (XML_ERROR_FILE_READ_ERROR);
    }
    XMLElement *el = saveFile.FirstChild()->FirstChildElement("Save");
    if (el == nullptr)
    {
        throw XMLError(XML_ERROR_PARSING_ELEMENT);
    }
    unsigned int saveIdRead;
    do
    {
        returnCode = el->QueryUnsignedAttribute("id", &saveIdRead);
        if (returnCode != XML_SUCCESS)
        {
            throw XMLError(returnCode);
        }
        if (saveIdRead != id)
        {
            el = el->NextSiblingElement("Save");
        }
    } while (el != nullptr && saveIdRead != id);
    if (saveIdRead != id)
    {
        throw XMLError(XML_ERROR_FILE_READ_ERROR);
    }
    return el;
}

const XMLElement *Player::getConstNodePlayerId(unsigned int id, XMLDocument &saveFile)
{
    const XMLElement *el = Player::getNodePlayerId(id, saveFile);
    return el;
}
