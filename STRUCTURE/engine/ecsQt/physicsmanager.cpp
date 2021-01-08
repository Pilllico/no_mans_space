#include "physicsmanager.h"

PhysicsManager::PhysicsManager()
{

}

void PhysicsManager::addComponent(Entity e, Component* component)
{
    data.insert(std::make_pair(e, *dynamic_cast<Physics*>(component)));
    //data.push_back(*dynamic_cast<Physics*>(component));
    //indices.insert(std::make_pair(e, data.size() - 1));
}

void PhysicsManager::deleteComponent(Entity e)
{
    data.erase(e);
}

Physics& PhysicsManager::getPhysics(Entity e)
{
    return data.at(e);
}

std::unordered_map<Entity, Physics, EntityHasher>& PhysicsManager::getAllPhysics()
{
    return data;
}
