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

#ifndef PLAYER_H
#define PLAYER_H
#define TIXML_USE_STL

#include <vector>
#include <iostream>
#include <map>
#include "const.h"
#include "TinyXml2/tinyxml2.h"

enum power_list{INVINCIBILITY, MAGNETISATION, SLOW_TIME, NB_POWER};

class Player
{
private:
    unsigned int m_bestScore;
    std::string m_nickName;
    unsigned int m_money;
    unsigned int m_id;
    unsigned int m_powerUpgrades[power_list::NB_POWER];     //Associe un pouvoir à une durée d'activation totale

    static tinyxml2::XMLElement *getNodePlayerId(unsigned int id, tinyxml2::XMLDocument &saveFile);     //Renvoi le noeud du fichier XML correspondant au joueur avex un certain ID
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
    unsigned int getTimePower(int power) const;

    static std::string getStringPower(unsigned int idPower, unsigned int langId);
    static void eraseProfil(unsigned int i);
    static bool isActive(unsigned int i);           //Un profil active est un profil que l'on peut charger. Une sauvegarde vide n'est pas active

};

#endif // PLAYER_H
