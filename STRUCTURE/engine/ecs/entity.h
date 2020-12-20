#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

class Entity
{
public:
    Entity();
private:
    unsigned short id;
    Entity* parent;
    std::vector<Entity*> children;
    static unsigned short lastID;
};

#endif // ENTITY_H
