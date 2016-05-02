#include "movableelement.h"

MovableElement::MovableElement(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod): Element{x, y, w, h, rotation}, m_movement{mx, my}, m_rotationMovement{rotationMovement}, m_lastMoveCall{}, m_movePeriod{movePeriod}
{

}

std::string MovableElement::getClassName() const
{
    return "MovableElement";
}

void MovableElement::move()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_lastMoveCall).count() >= m_movePeriod)
    {
        m_position.first += m_movement.first;
        m_position.second += m_movement.second;
        m_rotation += m_rotationMovement;
        m_lastMoveCall = std::chrono::system_clock::now();
    }
}

//Retourne la vitesse de l'objet par rapport à la vue en pixels/seconde
std::pair<float, float> MovableElement::getPixelSpeed() const
{
    return std::make_pair<float, float>((m_movement.first / m_movePeriod) * 1000, (m_movement.second / m_movePeriod) * 1000);
}

std::pair<float, float> MovableElement::getMovement() const
{
    return m_movement;
}

void MovableElement::setMovePeriod(float movePeriod)
{
    m_movePeriod = movePeriod;
}

void MovableElement::setMovement(float dx, float dy)
{
    m_movement.first = dx;
    m_movement.second = dy;
}
