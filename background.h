#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "element.h"
#include <chrono>

class Background: public Element
{
private:
    bool m_isSliding;
    std::string  m_backgroundFileName;
    std::chrono::time_point<std::chrono::system_clock> m_lastSlideCall;
    int m_slidePeriod;
    int m_zIndex;
public:
    Background(std::string backgroundFileName, int zIndex, bool isSliding = 0, int speedPeriodMicroSec = 0);
    virtual ~Background() = default;
    std::string getBackgroundFileName() const;
    int getZIndex() const;
    bool isSliding() const;
    void slide();
    std::string getClassName() const;
};

#endif // BACKGROUND_H
