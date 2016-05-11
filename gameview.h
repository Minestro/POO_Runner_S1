#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "view.hpp"

class GameView: public View<Game>
{
public:
    GameView() = default;
    virtual ~GameView() = default;
    bool treatEvent();
};

#endif // GAMEVIEW_H
