#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"

struct Component
{
    Component();
    virtual bitmap getBitMap() const = 0;
    virtual ~Component();
};

#endif // COMPONENT_H
