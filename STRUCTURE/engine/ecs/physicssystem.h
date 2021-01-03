#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "system.h"
#include "bullet/btBulletDynamicsCommon.h"

class physicsSystem : public System
{
public:
    physicsSystem();
    void virtual execute();
private:
    btDefaultCollisionConfiguration * collisionConfiguration;
    btCollisionDispatcher * dispatcher;
    btBroadphaseInterface * overlappingPairCache;
    btSequentialImpulseConstraintSolver * solver;
    btDiscreteDynamicsWorld * dynamicsWorld;
};

#endif // PHYSICSSYSTEM_H
