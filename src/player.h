#ifndef PLAYER_H
#define PLAYER_H
#define TIXML_USE_STL

#include <vector>
#include <iostream>
#include <map>
#include "const.h"
#include "TinyXml2/tinyxml2.h"

enum power_list{INVINCIBILITY, SLOW_TIME, FASTER_ASCEND, NB_POWER};

class Player
{
private:
    unsigned int m_bestScore;
    std::string m_nickName;
    unsigned int m_money;
    unsigned int m_id;
    unsigned int m_powerUpgrades[power_list::NB_POWER];     //Associe un pouvoir à une durée.

    static tinyxml2::XMLElement *getNodePlayerId(unsigned int id, tinyxml2::XMLDocument &saveFile);
    static const tinyxml2::XMLElement *getConstNodePlayerId(unsigned int id, tinyxml2::XMLDocument &saveFile);
public:
    Player();
    Player(unsigned int i);
    std::string getName() const;
    unsigned int getBestScore() const;
    unsigned int getId() const;
    void setNickName(std::string name);
    void setBestScore(unsigned int score);
    void saveProfile() const;
    void loadSaveFromFile();
    bool buy(unsigned int upgradeId);
    void addMoney(unsigned int money);
    unsigned int getMoney() const;
    unsigned int getTimePower(power_list power) const;

    static void eraseProfil(unsigned int i);
    static bool isActive(unsigned int i);

};

#endif // PLAYER_H
