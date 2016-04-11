#include "movableelement.h"

MovableElement::MovableElement(float x, float y, float w, float h, float mx, float my, int movePeriod): Element{x, y, w, h}, m_movement{mx, my}, m_lastMoveCall{}, m_movePeriod{movePeriod}
{

}

std::string MovableElement::getClassName() const
{
    return "MovableElement";
}

void MovableElement::move()
{
    if (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-m_lastMoveCall).count() > m_movePeriod)
    {
        m_position.first += m_movement.first;
        m_position.second += m_movement.second;
        m_lastMoveCall = std::chrono::system_clock::now();
    }
}

//Retourne la vitesse de l'objet par rapport à la vue en pixels/seconde
std::pair<float, float> MovableElement::getPixelSpeed() const
{
    return std::make_pair<float, float>((m_movement.first / m_movePeriod) * 1000000, (m_movement.second / m_movePeriod) * 1000000);
}

void MovableElement::setMovePeriod(float movePeriod)
{
    m_movePeriod = movePeriod;
}
