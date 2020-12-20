#include "entity.h"

unsigned short Entity::lastID = 0;

Entity::Entity()
{
    this->id = lastID;
    lastID++;
}
