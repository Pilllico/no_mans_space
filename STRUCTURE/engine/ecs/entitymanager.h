#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>
#include <bitset>

#include "subject.h"
#include "entity.h"
#include "component.h"

class EntityManager : public Subject
{
public:
    EntityManager();
    Entity createEntity();
    void addComponentToEntity(Component* component, Entity e);
    void addComponentsToEntity(std::vector<Component*> components, Entity e);
    std::bitset<16> getBitMapFromEntity(Entity e);
    std::vector<Component*> getComponentsFromEntity(std::bitset<16> bitset, Entity e);
    bool deleteEntity(Entity e);
    bool deleteComponentsFromEntity(std::bitset<16> bitset, Entity e);
private:
    std::unordered_map<Entity, std::bitset<16>> entityList;
    std::unordered_map<std::bitset<16>, std::vector<Component*>> componentsList;
};

#endif // ENTITYMANAGER_H
