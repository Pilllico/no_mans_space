#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <set>
#include <utility>

#include "entity.h"
#include "component.h"
#include "componentmanager.h"

#include "transform.h"
#include "transformmanager.h"
#include "physics.h"
#include "physicsmanager.h"

class System;

class EntityManager
{
public:
    static EntityManager & getInstance();
    Entity createEntity();

    void addComponentToEntity(Entity e, Component* component);
    void addComponentToEntity(Entity e, QVector3D pos, QVector3D rot, QVector3D s);
    void addComponentToEntity(Entity e, float m, CollisionShape cs);

    void addComponentsToEntity(Entity e, std::vector<Component*> components);

    bitmap getBitMapFromEntity(Entity e);

    ComponentManager* getComponentManagerForSystem(bitmap bitset);
    std::vector<ComponentManager*> getComponentManagersForSystem(bitmap bitset);

    bool deleteEntity(Entity e);
    bool deleteComponentsFromEntity(bitmap bitset, Entity e);
    void registerSystem(System * system);
    ~EntityManager();
private:
    EntityManager();
    std::unordered_map<Entity, bitmap, EntityHasher> entitiesList;
    std::unordered_map<bitmap, ComponentManager*> componentManagers;

    std::set<System*> systemList;

    void notifyAll(Entity e);
};

#endif // ENTITYMANAGER_H
