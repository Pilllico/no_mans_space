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

    dynamicsWorld->setGravity(btVector3(0, 0, -9.81f));
}

bool physicsSystem::execute()
{
    std::cout << "Start Physics system" << std::endl;
    std::clock_t now = std::clock();
    float diff = static_cast<float>(difftime(now, time));
    time = now;

    std::cout << diff << std::endl;

    std::cout << "AAA" << std::endl;
    dynamicsWorld->stepSimulation(diff/1000.0f, 10);

    std::cout << "End Physics system" << std::endl;

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

            TransformManager* transformManager = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")));
            Transform& transform = transformManager->getTransform(e);

            dynamicsWorld->removeRigidBody(data.at(e).second);
            delete transform.motionState;
            delete data.at(e).second;
            delete data.at(e).first;
            data.erase(e);

        }
    }
    else {
        if ((signature&systemSignature) == systemSignature) {
            // create new MotionState for bullet
            // TODO

            std::cout <<"TEST1" << std::endl;

            TransformManager* transformManager = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")));
            std::cout <<"TEST2" << std::endl;

            PhysicsManager* physicsManager = dynamic_cast<PhysicsManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1000")));
            std::cout <<"TEST3" << std::endl;

            Transform& transform = transformManager->getTransform(e);
            std::cout <<"TEST4" << std::endl;

            Physics& physics = physicsManager->getPhysics(e);

            std::cout <<"TEST5" << std::endl;

            transform.motionState = new MotionState(&transform);

            btCollisionShape* collisionShape;

            if (physics.collisionShape == Sphere)
                collisionShape = new btSphereShape(std::max(transform.scale.x(), std::max(transform.scale.y(),transform.scale.z())));
            else
                collisionShape = new btBoxShape(btVector3(transform.scale.x(), transform.scale.y(), transform.scale.z()));

            btRigidBody* rigidBody = new btRigidBody(physics.mass, transform.motionState, collisionShape);

            std::cout <<"TEST6" << std::endl;

            dynamicsWorld->addRigidBody(rigidBody);

            data.insert(std::make_pair(e, std::make_pair(collisionShape, rigidBody)));

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
