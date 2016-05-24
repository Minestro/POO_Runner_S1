#ifndef BONUS_H
#define BONUS_H

#include "movableelement.h"

enum bonus_type{COIN, INVINSIBLE, MAGNET, MEDIC, SLOW_TIME_BONUS};

class Bonus: public MovableElement
{
private:
    int m_type;    //Le type de bonus ou de maluce !!!
public:
    Bonus(float x, float y, float w, float h, float rotation, float mx, float my, float rotationMovement, int movePeriod, int type);
    virtual ~Bonus() = default;
    std::string getClassName() const;
    int getType() const;
};

#endif // BONUS_H

