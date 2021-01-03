#include "physicssystem.h"

physicsSystem::physicsSystem()
{
    time = std::clock();
    systemSignature = bitmap("00001001");

    collisionConfiguration = new btDefaultCollisionConfiguration ();
    dispatcher = new btCollisionDispatcher ( collisionConfiguration );
    overlappingPairCache = new btDbvtBroadphase ();
    solver = new btSequentialImpulseConstraintSolver ;
    dynamicsWorld = new btDiscreteDynamicsWorld ( dispatcher, overlappingPairCache, solver, collisionConfiguration);
}

bool physicsSystem::execute()
{
    std::clock_t now = std::clock();
    float diff = static_cast<float>(difftime(now, time));
    time = now;

    dynamicsWorld->stepSimulation(diff, 10);

    //std::cout << "The physics system detect " << entityList.size() << " entities" << std::endl;

    return true;
}

physicsSystem::~physicsSystem()
{
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;
}
