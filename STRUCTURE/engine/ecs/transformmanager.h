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
private:
    std::vector<Transform> data;
    std::unordered_map<Entity, unsigned short> indices;
};

#endif // TRANSFORMMANAGER_H
