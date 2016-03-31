#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "element.h"
#include "game.h"

class Background: public Element
{
private:
    bool m_isSliding;
    std::string  m_backgroundFileName;
public:
    Background(std::string backgroundFileName, bool isSliding = 0);
    std::string getBackgroundFileName() const;
    std::string getClassName() const;
};

#endif // BACKGROUND_H
