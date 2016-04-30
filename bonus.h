#ifndef BONUS_H
#define BONUS_H

#include "movableelement.h"
enum bonus_state{PIECE, INVINSIBLE, DOUBLESAUT};

class Bonus: public MovableElement
{
private:
    bonus_state m_type;    //Le type de bonus ou de maluce !!!
public:
    Bonus(float x, float y, float w, float h, float mx, float my, int movePeriod, bonus_state type);
    virtual ~Bonus() = default;
    std::string getClassName() const;
    bonus_state getState() const;
};

#endif // BONUS_H

