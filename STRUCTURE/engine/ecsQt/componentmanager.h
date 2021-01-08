#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "component.h"
#include <unordered_map>

class ComponentManager
{
public:
    ComponentManager();
    virtual void addComponent(Entity e, Component* component) = 0;
    virtual void deleteComponent(Entity e) = 0;
    virtual ~ComponentManager();
    std::unordered_map<Entity, unsigned short, EntityHasher>& getAllIndices();
protected:
    //std::unordered_map<Entity, unsigned short, EntityHasher> indices;
};

#endif // COMPONENTMANAGER_H
