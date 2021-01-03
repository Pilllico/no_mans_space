#include "componentmanager.h"

ComponentManager::ComponentManager()
{

}

ComponentManager::~ComponentManager()
{

}

std::unordered_map<Entity, unsigned short, EntityHasher>& ComponentManager::getAllIndices()
{
    return indices;
}
