#include "entity.h"

unsigned short Entity::lastID = 0;

Entity::Entity()
{
    this->id = lastID;
    lastID++;
}

bool Entity::isEqual(Entity const& a) const
{
    return this->id == a.id;
}

/*bool Entity::operator==(Entity const& e)
{
    return this->id == e.id;
};*/

bool operator==(Entity const& e, Entity const& f)
{
    return e.id == f.id;
};
