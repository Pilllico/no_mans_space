#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <set>
#include <utility>

#include "entity.h"
#include "component.h"
#include "transform.h"
#include "transformmanager.h"
#include "componentmanager.h"

class System;

class EntityManager
{
public:
    static EntityManager & getInstance();
    Entity createEntity();

    void addComponentToEntity(Component* component, Entity e);
    void addComponentsToEntity(std::vector<Component*> components, Entity e);

    bitmap getBitMapFromEntity(Entity e);

    std::vector<ComponentManager*> getComponentManagersForSystem(bitmap bitset);

    bool deleteEntity(Entity e);
    bool deleteComponentsFromEntity(bitmap bitset, Entity e);
    void registerSystem(System * system);
    ~EntityManager();
private:
    EntityManager();
    std::unordered_map<Entity, bitmap, EntityHasher> entitiesList;
    std::vector<ComponentManager*> componentManagers;

    std::set<System*> systemList;
    //static EntityManager* instance;

    void notifyAll(bitmap signature, Entity e);
};

#endif // ENTITYMANAGER_H
