#include "image.h"

Image::Image(float x, float y, float width, float height, std::string backgroundFileName, int zIndex, float coefSpeed, bool isSliding, int movePeriodMicroSec):MovableElement{x, y, width, height, 0, -PIXELPERBACKGROUNDMOVE, 0, 0, movePeriodMicroSec}, m_isSliding{isSliding}, m_backgroundFileName{backgroundFileName}, m_zIndex{zIndex}, m_coefSpeed{coefSpeed}
{

}

std::string Image::getClassName() const
{
    return "Background";
}

std::string Image::getBackgroundFileName() const
{
    return m_backgroundFileName;
}

void Image::move()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastMoveCall).count() > m_movePeriod && m_isSliding)
    {
        if (m_position.first - (m_movement.first * m_coefSpeed) > -m_size.first)
        {
            m_position.first += m_movement.first * m_coefSpeed;
        } else {
            m_position.first = 0;
        }
        m_lastMoveCall = std::chrono::system_clock::now();
    }
}

int Image::getZIndex() const
{
    return m_zIndex;
}

bool Image::isSliding() const
{
    return m_isSliding;
}

float Image::getCoefSpeed() const
{
    return m_coefSpeed;
}
