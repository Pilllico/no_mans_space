#include "transformmanager.h"

TransformManager::TransformManager()
{

}

void TransformManager::addComponent(Entity e, Component* component) {
    data.insert(std::make_pair(e, *dynamic_cast<Transform*>(component)));
    //data.push_back(*dynamic_cast<Transform*>(component));
    //indices.insert(std::make_pair(e, data.size() - 1));
}

void TransformManager::deleteComponent(Entity e) {

    data.erase(e);

    /*int indice = indices.at(e);

    for (auto& p : indices) {
        if (p.second > indice)
            p.second--;
    }

    data.erase(data.begin() + indice);*/
}

Transform& TransformManager::getTransform(Entity e)
{
    return data.at(e);
}

std::unordered_map<Entity, Transform, EntityHasher>& TransformManager::getAllTransforms()
{
    return data;
}
