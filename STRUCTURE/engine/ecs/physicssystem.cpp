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

    //std::vector<>;

    for (Entity e : entityList) {

    }

    //std::cout << "The physics system detect " << entityList.size() << " entities" << std::endl;

    return true;
}

void physicsSystem::update(Entity e)
{
    // Entity e has new signature
    bitmap signature = EntityManager::getInstance().getBitMapFromEntity(e);

    std::cout << "Notified" << std::endl;

    if (find(entityList.begin(), entityList.end(), e) != entityList.end()) {
        if ((signature&systemSignature) != systemSignature) {
            entityList.erase(find(entityList.begin(), entityList.end(), e));
        }
    }
    else {
        if ((signature&systemSignature) == systemSignature) {
            // create new Motion for bullet
            // TODO
            entityList.push_back(e);
        }
    }
}

physicsSystem::~physicsSystem()
{
    delete dynamicsWorld;
    delete solver;
    delete overlappingPairCache;
    delete dispatcher;
    delete collisionConfiguration;
}
