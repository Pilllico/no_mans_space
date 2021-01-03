#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "componentmanager.h"
#include "physics.h"

class PhysicsManager : public ComponentManager
{
public:
    PhysicsManager();
    virtual void addComponent(Entity e, Component* component);
    virtual void deleteComponent(Entity e);
    const Physics& getPhysics(Entity e);
    std::vector<Physics> getPhysics(std::vector<Entity> entitiesList);
    std::vector<Physics>& getAllPhysics();
private:
    std::vector<Physics> data;
};

#endif // PHYSICSMANAGER_H
