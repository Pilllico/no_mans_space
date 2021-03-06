#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "system.h"
#include "bullet/btBulletDynamicsCommon.h"
#include <ctime>

class physicsSystem : public System
{
public:
    physicsSystem();
    bool virtual execute();
    virtual void update(Entity e);
    ~physicsSystem();
	std::unordered_map<Entity, std::pair<btCollisionShape*, btRigidBody*>, EntityHasher>& getData();
private:
    btDefaultCollisionConfiguration * collisionConfiguration;
    btCollisionDispatcher * dispatcher;
    btBroadphaseInterface * overlappingPairCache;
    btSequentialImpulseConstraintSolver * solver;
    btDiscreteDynamicsWorld * dynamicsWorld;
    std::clock_t time;
    std::unordered_map<Entity, std::pair<btCollisionShape*, btRigidBody*>, EntityHasher> data;
};

#endif // PHYSICSSYSTEM_H
