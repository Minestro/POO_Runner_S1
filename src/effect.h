#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.hpp>
#include <chrono>

enum filter_effect{NOTHING, BREATH, FLASH};

struct Effect
{
    Effect();
    int m_filterEffect;
    unsigned int m_refreshPeriod;
    std::chrono::time_point<std::chrono::system_clock> m_lastRefeshCall;
    sf::RenderStates m_states;
    sf::Color m_firstColor;
    sf::Color m_secondColor;
    sf::Color m_colorFilter;
};

#endif // EFFECT_H
