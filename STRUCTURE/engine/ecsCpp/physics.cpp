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
	this->gravityStrength = 9.81;
	this->collisionShape = cs;
}

Physics::Physics(float mass, float strength, CollisionShape cs)
{
    this->mass = mass;
	this->gravityStrength = strength;
    this->collisionShape = cs;
}

Physics::Physics(float mass, float strength, CollisionShape cs, bool ctrl)
{
	this->mass = mass;
	this->gravityStrength = strength;
	this->collisionShape = cs;
	this->isController = ctrl;
}

bitmap Physics::getBitMap() const
{
    return componentSignature;
}

Physics::~Physics()
{

}
