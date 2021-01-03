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
    ~physicsSystem();
private:
    btDefaultCollisionConfiguration * collisionConfiguration;
    btCollisionDispatcher * dispatcher;
    btBroadphaseInterface * overlappingPairCache;
    btSequentialImpulseConstraintSolver * solver;
    btDiscreteDynamicsWorld * dynamicsWorld;
    std::clock_t time;
};

#endif // PHYSICSSYSTEM_H
