#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"

struct Component
{
public:
    virtual bitmap getBitMap() = 0;
    virtual ~Component();
protected:
    bitmap id;
};

#endif // COMPONENT_H
