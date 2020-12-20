#include "transformmanager.h"

TransformManager::TransformManager()
{

}

void TransformManager::addComponent(Entity e, Component* component) {
    data.push_back(*dynamic_cast<Transform*>(component));
    indices.insert(std::make_pair(e, data.size() - 1));
}
