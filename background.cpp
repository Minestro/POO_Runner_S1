#include "background.h"

Background::Background(std::string backgroundFileName, int zIndex, bool isSliding, int movePeriodMicroSec):MovableElement{0, 0, GAME_SIZE_W, GAME_SIZE_H, -3, 0, movePeriodMicroSec}, m_isSliding{isSliding}, m_backgroundFileName{backgroundFileName}, m_zIndex{zIndex}
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

void Background::move()
{
    if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-m_lastMoveCall).count() > m_movePeriod && m_isSliding)
    {
        if (m_position.first - 10 > -m_size.first)
        {
            m_position.first += m_movement.first;
        } else {
            m_position.first = 0;
        }
        m_lastMoveCall = std::chrono::system_clock::now();
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
