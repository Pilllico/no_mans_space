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
    Transform& getTransform(Entity e);
    std::unordered_map<Entity, Transform, EntityHasher>& getAllTransforms();
private:
    //std::vector<Transform> data;
    std::unordered_map<Entity, Transform, EntityHasher> data;
};

#endif // TRANSFORMMANAGER_H
