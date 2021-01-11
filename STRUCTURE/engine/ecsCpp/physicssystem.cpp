#include "physicssystem.h"
#include <algorithm>
#include <limits>

physicsSystem::physicsSystem()
{
    time = std::clock();
    systemSignature = bitmap("00001001");

    collisionConfiguration = new btDefaultCollisionConfiguration ();
    dispatcher = new btCollisionDispatcher ( collisionConfiguration );
    overlappingPairCache = new btDbvtBroadphase ();
    solver = new btSequentialImpulseConstraintSolver ;
    dynamicsWorld = new btDiscreteDynamicsWorld ( dispatcher, overlappingPairCache, solver, collisionConfiguration);

    //dynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));
}

bool physicsSystem::execute()
{
    std::clock_t now = std::clock();
    float diff = static_cast<float>(difftime(now, time));
    time = now;

	// TO DO : controllerSystem
	/*
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		data.at(controller).second->applyCentralImpulse(btVector3(direction.x, direction.y, direction.z));
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		data.at(controller).second->applyCentralImpulse(-btVector3(direction.x, direction.y, direction.z));
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		data.at(controller).second->applyCentralImpulse(btVector3(right.x, right.y, right.z));
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		data.at(controller).second->applyCentralImpulse(-btVector3(right.x, right.y, right.z));
	}
	*/

	btVector3 planet;

	for (auto pair : data) {
		btRigidBody* rBody = pair.second.second;

		if (rBody->getMass() == 0.0f) {
			Entity e = pair.first;
			const Transform& transform = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")))->getTransform(e);

			planet = transform.position;
		}
	}

	for (auto pair : data) {
		btRigidBody* rBody = pair.second.second;

		if (rBody->getMass() > 0.0f) {

			Entity e = pair.first;
			const Transform& transform = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")))->getTransform(e);
			const Physics& physics = dynamic_cast<PhysicsManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1000")))->getPhysics(e);

			btScalar dist = (planet - transform.position).length();
			btVector3 dir = (planet - transform.position).normalize();
			btScalar strength = physics.gravityStrength / ( dist/10.0f * dist/10.0f );

			rBody->setGravity(strength * dir);
		}
	}

    dynamicsWorld->stepSimulation(diff/1000.0f, 10);

    return true;
}

void physicsSystem::update(Entity e)
{
    // Entity e has new signature
    bitmap signature = EntityManager::getInstance().getBitMapFromEntity(e);

    std::cout << "System " << systemSignature << " notified" << std::endl;

	// New entity
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
	// Existing entity, new signature
    else {
        if ((signature&systemSignature) == systemSignature) {

			Transform& transform = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")))->getTransform(e);

			const Physics& physics = dynamic_cast<PhysicsManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1000")))->getPhysics(e);

			//if (physics.isController)
			//	controller = e;

            transform.motionState = new MotionState(&transform);

            btCollisionShape* collisionShape;

            if (physics.collisionShape == Sphere) {
                collisionShape = new btSphereShape(std::max(transform.scale.x(), std::max(transform.scale.y(), transform.scale.z())));
            }
            else
                collisionShape = new btBoxShape(btVector3(transform.scale.x(), transform.scale.y(), transform.scale.z()));

            btRigidBody::btRigidBodyConstructionInfo bodyCI(physics.mass, transform.motionState, collisionShape);
            //bodyCI.m_restitution = btScalar(0.2f);
            //bodyCI.m_friction = btScalar(0.2f);
            //bodyCI.m_linearSleepingThreshold = btScalar(0.0f);
            //bodyCI.m_angularSleepingThreshold = btScalar(0.0f);

            btRigidBody* rigidBody = new btRigidBody(bodyCI);

			rigidBody->setFlags(rigidBody->getFlags() | BT_DISABLE_WORLD_GRAVITY);
			
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

std::unordered_map<Entity, std::pair<btCollisionShape*, btRigidBody*>, EntityHasher>& physicsSystem::getData()
{
	return data;
}

/*Entity physicsSystem::getController()
{
	return controller;
}*/