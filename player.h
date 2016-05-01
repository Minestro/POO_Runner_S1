#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <map>

enum power_list{INVINCIBILITY, SLOW_TIME, FASTER_ASCEND, NB_POWER};

class Player
{
private:
    unsigned int m_bestScore;
    std::string m_nickName;
    unsigned int m_money;
    unsigned int m_powerUpgrades[power_list::NB_POWER - 1];     //Associe un pouvoir à une durée.

public:
    Player();
    void saveProfile() const;
    void loadProfile();
};

#endif // PLAYER_H
