#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "element.h"

class Background: public Element
{
private:
    bool m_isSliding;
    std::string  m_backgroundFileName;
    sf::Clock m_speedClock;
    unsigned int m_speedPeriod;
public:
    Background(std::string backgroundFileName, bool isSliding = 0, unsigned int speedPeriod = 0);
    std::string getBackgroundFileName() const;
    bool isSliding() const;
    void slide();
    std::string getClassName() const;
};

#endif // BACKGROUND_H
