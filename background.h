#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "movableelement.h"

class Background: public MovableElement
{
private:
    bool m_isSliding;
    std::string  m_backgroundFileName;
    int m_zIndex;
public:
    Background(std::string backgroundFileName, int zIndex, bool isSliding = 0, int movePeriodMicroSec = 0);
    virtual ~Background() = default;
    std::string getBackgroundFileName() const;
    int getZIndex() const;
    bool isSliding() const;
    void move() override;
    std::string getClassName() const;
};

#endif // BACKGROUND_H
