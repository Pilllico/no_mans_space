#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "component.h"

class ComponentManager
{
public:
    ComponentManager();
    virtual void addComponent(Entity e, Component* component) = 0;
    virtual void deleteComponent(Entity e) = 0;
    virtual ~ComponentManager();
    bitmap id;
};

#endif // COMPONENTMANAGER_H
