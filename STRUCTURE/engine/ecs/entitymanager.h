#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <bitset>
#include <set>
#include <utility>

#include "subject.h"
#include "entity.h"
#include "component.h"
#include "transform.h"
#include "transformmanager.h"
#include "componentmanager.h"

class System;

class EntityManager
{
public:
    static EntityManager * getInstance();
    Entity createEntity();


    void addComponentToEntity(Component* component, Entity e);

    void addComponentsToEntity(std::vector<Component*> components, Entity e);


    std::bitset<16> getBitMapFromEntity(Entity e);
    std::vector<Component*> getComponentsFromEntity(std::bitset<16> bitset, Entity e);
    bool deleteEntity(Entity e);
    bool deleteComponentsFromEntity(std::bitset<16> bitset, Entity e);
    ~EntityManager();
private:
    EntityManager();
    std::unordered_map<Entity, std::bitset<16>> entitiesList;
    std::vector<ComponentManager*> componentManagers;

    std::vector<Transform> transformList;

    std::set<System*> systemList;
    static EntityManager* instance;

    void notifyAll();
};

#endif // ENTITYMANAGER_H
