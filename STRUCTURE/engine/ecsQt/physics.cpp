#include "physics.h"

Physics::Physics()
{
    mass = 1.0f;
    collisionShape = Sphere;
}

Physics::Physics(float mass) : Physics()
{
    this->mass = mass;
}

Physics::Physics(float mass, CollisionShape cs)
{
    this->mass = mass;
    this->collisionShape = cs;
}

bitmap Physics::getBitMap() const
{
    return componentSignature;
}

Physics::~Physics()
{

}
