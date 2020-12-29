#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include "entitymanager.h"

class EntityManager;

class System
{
public:
    System();
    void update(bitmap signature, Entity e);
    void virtual execute() = 0;
    virtual ~System();
protected:
    bitmap systemSignature;
    std::vector<Entity> entityList;
    EntityManager& entityManager = EntityManager::getInstance();
};

#endif // SYSTEM_H
