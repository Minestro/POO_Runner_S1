#include "background.h"

Background::Background(std::string backgroundFileName, bool isSliding, int speedPeriod):Element{0, 0, GAME_SIZE_W, GAME_SIZE_H}, m_isSliding{isSliding}, m_backgroundFileName{backgroundFileName}, m_slidePeriod{speedPeriod}
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
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastSlideCall).count() > m_slidePeriod)
    {
        if (m_position.first - 10 > -m_size.first)
        {
            m_position.first -= 10.0;
        } else {
            m_position.first = 0;
        }
        m_lastSlideCall = std::chrono::system_clock::now();
    }
}

bool Background::isSliding() const
{
    return m_isSliding;
}
