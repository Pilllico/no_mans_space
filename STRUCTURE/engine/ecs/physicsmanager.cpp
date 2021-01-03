#include "physicsmanager.h"

PhysicsManager::PhysicsManager()
{

}

void PhysicsManager::addComponent(Entity e, Component* component)
{
    data.push_back(*dynamic_cast<Physics*>(component));
    indices.insert(std::make_pair(e, data.size() - 1));
}

void PhysicsManager::deleteComponent(Entity e)
{
    int indice = indices.at(e);

    for (auto& p : indices) {
        if (p.second > indice)
            p.second--;
    }

    data.erase(data.begin() + indice);
}

const Physics& PhysicsManager::getPhysics(Entity e)
{
    return data.at(indices.at(e));
}

std::vector<Physics> PhysicsManager::getPhysics(std::vector<Entity> entitiesList)
{
    std::vector<Physics> out;

    for (Entity& e : entitiesList)
    {
        out.push_back(data.at(indices.at(e)));
    }
    return out;
}

std::vector<Physics>& PhysicsManager::getAllPhysics()
{
    return data;
}
