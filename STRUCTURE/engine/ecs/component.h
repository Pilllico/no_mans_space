#ifndef COMPONENT_H
#define COMPONENT_H

#include "entity.h"

class Component
{
public:
    Component();
    virtual bitmap getBitMap() const = 0;
    virtual ~Component();
};

#endif // COMPONENT_H
