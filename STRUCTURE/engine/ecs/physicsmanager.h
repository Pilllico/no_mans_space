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
    Physics& getPhysics(Entity e);
    std::unordered_map<Entity, Physics, EntityHasher>& getAllPhysics();
private:
    //std::vector<Physics> data;
    std::unordered_map<Entity, Physics, EntityHasher> data;
};

#endif // PHYSICSMANAGER_H
