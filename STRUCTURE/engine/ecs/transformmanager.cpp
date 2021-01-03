#include "transformmanager.h"

TransformManager::TransformManager()
{

}

void TransformManager::addComponent(Entity e, Component* component) {
    data.push_back(*dynamic_cast<Transform*>(component));
    indices.insert(std::make_pair(e, data.size() - 1));
}

void TransformManager::deleteComponent(Entity e) {

    int indice = indices.at(e);

    for (auto& p : indices) {
        if (p.second > indice)
            p.second--;
    }

    data.erase(data.begin() + indice);
}

const Transform& TransformManager::getTransform(Entity e)
{
    return data.at(indices.at(e));
}

std::vector<Transform> TransformManager::getTransforms(std::vector<Entity> entitiesList)
{
    std::vector<Transform> out;

    for (Entity& e : entitiesList)
    {
        out.push_back(data.at(indices.at(e)));
    }
    return out;
}

std::vector<Transform>& TransformManager::getAllTransforms()
{
    return data;
}
