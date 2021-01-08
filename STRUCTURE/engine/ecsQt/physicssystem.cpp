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

    dynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));
}

bool physicsSystem::execute()
{
    std::clock_t now = std::clock();
    float diff = static_cast<float>(difftime(now, time));
    time = now;

    dynamicsWorld->stepSimulation(diff/1000.0f, 10);

    return true;
}

void physicsSystem::update(Entity e)
{
    // Entity e has new signature
    bitmap signature = EntityManager::getInstance().getBitMapFromEntity(e);

    std::cout << "System " << systemSignature << " notified" << std::endl;

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

            Transform& transform = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")))->getTransform(e);

            Physics& physics = dynamic_cast<PhysicsManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1000")))->getPhysics(e);

            transform.motionState = new MotionState(&transform);

            btCollisionShape* collisionShape;

            if (physics.collisionShape == Sphere) {
                collisionShape = new btSphereShape(0.5f * std::max(transform.scale.x(), std::max(transform.scale.y(), transform.scale.z())));
            }
            else
                collisionShape = new btBoxShape(btVector3(transform.scale.x(), transform.scale.y(), transform.scale.z()));

            btRigidBody::btRigidBodyConstructionInfo bodyCI(physics.mass, transform.motionState, collisionShape);
            bodyCI.m_restitution = btScalar(0.5f);
            bodyCI.m_friction = btScalar(0.0f);
            //bodyCI.m_linearSleepingThreshold = btScalar(0.0f);
            //bodyCI.m_angularSleepingThreshold = btScalar(0.0f);

            btRigidBody* rigidBody = new btRigidBody(bodyCI);

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
