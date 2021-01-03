#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H

#include <unordered_map>
#include "transform.h"
#include "entity.h"
#include "componentmanager.h"

class TransformManager : public ComponentManager
{
public:
    TransformManager();
    virtual void addComponent(Entity e, Component* component);
    virtual void deleteComponent(Entity e);
    const Transform& getTransform(Entity e);
    std::vector<Transform> getTransforms(std::vector<Entity> entitiesList);
    std::vector<Transform>& getAllTransforms();
private:
    std::vector<Transform> data;
};

#endif // TRANSFORMMANAGER_H
