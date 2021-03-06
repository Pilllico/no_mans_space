#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "entitymanager.h"
#include <iostream>

class EntityManager;

class System
{
public:
    System();
    virtual void update(Entity e);
    bool virtual execute() = 0;
    virtual ~System();
protected:
    bitmap systemSignature;
    std::vector<Entity> entityList;
    EntityManager& entityManager = EntityManager::getInstance();
};

#endif // SYSTEM_H
