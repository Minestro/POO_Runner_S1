#ifndef BONUS_H
#define BONUS_H

#include "movableelement.h"

class Bonus: public MovableElement
{
private:
    unsigned int m_type;    //Le type de bonus ou de maluce !!!
public:
    unsigned int getType() const;
    std::string getClassName() const override;
};

#endif // BONUS_H
