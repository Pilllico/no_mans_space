#include "physicssystem.h"

physicsSystem::physicsSystem()
{
    systemSignature = bitmap("00001001");

    collisionConfiguration = new btDefaultCollisionConfiguration ();
    dispatcher = new btCollisionDispatcher ( collisionConfiguration );
    overlappingPairCache = new btDbvtBroadphase ();
    solver = new btSequentialImpulseConstraintSolver ;
    dynamicsWorld = new btDiscreteDynamicsWorld ( dispatcher, overlappingPairCache, solver, collisionConfiguration);
}

void physicsSystem::execute()
{
    delete collisionConfiguration;
    delete dispatcher;
    delete overlappingPairCache;
    delete solver;
    delete dynamicsWorld;
}
