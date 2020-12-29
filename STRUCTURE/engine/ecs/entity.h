#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <bitset>

using bitmap = std::bitset<8>;

class Entity
{
public:
    Entity();
    bool isEqual(Entity const& e) const;
    unsigned short id;
    //bool operator==(Entity const& e);
    friend bool operator==(Entity const& e, Entity const& f);
private:
    Entity* parent;
    std::vector<Entity*> children;
    static unsigned short lastID;
};

struct EntityHasher
{
    std::size_t operator()(const Entity& E) const
    {
        using std::size_t;
        using std::hash;

        return hash<unsigned short>()(E.id);
    }
};

#endif // ENTITY_H
