#include "player.h"

Player::Player(): m_bestScore{0}, m_nickName{"guest"}, m_money{0}, m_powerUpgrades{}
{
    for (unsigned int i = 0; i<power_list::NB_POWER-1; i++)
    {
        m_powerUpgrades[i] = 7000;
    }
}
