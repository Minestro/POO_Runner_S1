#include "background.h"

Background::Background(std::string backgroundFileName, int zIndex, bool isSliding, int speedPeriodMicroSec):Element{0, 0, GAME_SIZE_W, GAME_SIZE_H}, m_isSliding{isSliding}, m_backgroundFileName{backgroundFileName}, m_slidePeriod{speedPeriodMicroSec}, m_zIndex{zIndex}
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
    if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-m_lastSlideCall).count() > m_slidePeriod && m_isSliding)
    {
        if (m_position.first - 10 > -m_size.first)
        {
            m_position.first -= 3.0;
        } else {
            m_position.first = 0;
        }
        m_lastSlideCall = std::chrono::system_clock::now();
    }
}

int Background::getZIndex() const
{
    return m_zIndex;
}

bool Background::isSliding() const
{
    return m_isSliding;
}
