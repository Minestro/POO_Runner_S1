#include "background.h"

Background::Background(std::string backgroundFileName, bool isSliding):Element{0, 0, GAME_SIZE_W, GAME_SIZE_H}, m_isSliding{isSliding}, m_backgroundFileName{backgroundFileName}
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
