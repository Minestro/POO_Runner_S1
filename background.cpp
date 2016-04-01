#include "background.h"

Background::Background(std::string backgroundFileName, bool isSliding, unsigned int speedPeriod):Element{0, 0, GAME_SIZE_W, GAME_SIZE_H}, m_isSliding{isSliding}, m_backgroundFileName{backgroundFileName}, m_speedClock{}, m_speedPeriod{speedPeriod}
{

}

std::string Background::getClassName() const
{
    return "Background";
}

std::string Background::getBackgroundFileName() const
{
    return m_backgroundFileName;
}

void Background::slide()
{
    if (m_speedClock.getElapsedTime().asMilliseconds() > m_speedPeriod && m_isSliding)
    {
        if (m_position.first - 1 > -(m_size.first/2))
        {
            m_position.first -= 1.0;
        }
        m_speedClock.restart();
    }
}

bool Background::isSliding() const
{
    return m_isSliding;
}
