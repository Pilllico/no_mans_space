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

float Physics::getMass() const
{
    return mass;
}

CollisionShape Physics::getCollisionShape() const
{
    return collisionShape;
}

bitmap Physics::getBitMap() const {
    return componentSignature;
}
