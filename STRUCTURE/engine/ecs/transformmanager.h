#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H

#include <unordered_map>
#include <transform.h>
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
    //static bitmap managerSignature;
private:
    std::vector<Transform> data;
    std::unordered_map<Entity, unsigned short, EntityHasher> indices;
};

#endif // TRANSFORMMANAGER_H
