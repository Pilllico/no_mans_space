#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "system.h"

class physicsSystem : public System
{
public:
    physicsSystem();
    void virtual execute();
};

#endif // PHYSICSSYSTEM_H
