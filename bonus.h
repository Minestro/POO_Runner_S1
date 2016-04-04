#ifndef BONUS_H
#define BONUS_H

#include "movableelement.h"

class Bonus: public MovableElement
{
private:
    unsigned int m_type;    //Le type de bonus ou de maluce !!!
public:
    virtual ~Bonus();
    unsigned int getType() const;
    std::string getClassName() const;
};

#endif // BONUS_H
