#ifndef SYSTEM_H
#define SYSTEM_H

#include "entity.h"
#include <vector>
#include "entitymanager.h"

class EntityManager;

class System
{
public:
    System();
    virtual void update(/*TO DO : argument*/) = 0;
    virtual ~System();
private:
    std::vector<Entity> entityList;
    EntityManager* entityManager = EntityManager::getInstance();
};

#endif // SYSTEM_H
