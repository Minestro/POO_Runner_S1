#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Player
{
private:
    unsigned int m_bestScore;
    std::string m_nickName;
    unsigned int m_money;


public:
    void saveProfile() const;
    void loadProfile();
};

#endif // PLAYER_H
