#include "physicssystem.h"
#include <algorithm>
#include <limits>

#include "render.h"

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

	std::vector<btVector3> planets;

	for (auto pair : data) {
		btRigidBody* rBody = pair.second.second;

		if (rBody->getMass() == 0.0f) {
			Entity e = pair.first;
			const Transform& transform = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")))->getTransform(e);

			planets.push_back(transform.position);
		}
	}

	for (auto pair : data) {
		btRigidBody* rBody = pair.second.second;

		if (rBody->getMass() > 0.0f) {

			Entity e = pair.first;
			const Transform& transform = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")))->getTransform(e);
			const Physics& physics = dynamic_cast<PhysicsManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1000")))->getPhysics(e);

			btVector3 direction = btVector3(0.0f, 0.0f, 0.0f);

			for (btVector3 planet : planets) {
				btScalar dist = (planet - transform.position).length();
				btVector3 dir = (planet - transform.position).normalize();
				btScalar strength = physics.gravityStrength / (dist / 10.0f * dist / 10.0f);
				direction += strength * dir;
			}

			rBody->setGravity(direction);
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
			const Render& render = dynamic_cast<RenderManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("10")))->getRender(e);

            transform.motionState = new MotionState(&transform);

            btCollisionShape* collisionShape;

            if (physics.collisionShape == Sphere) {
                collisionShape = new btSphereShape(std::max(transform.scale.x(), std::max(transform.scale.y(), transform.scale.z())));
            }
			else if (physics.collisionShape == Box) {
				collisionShape = new btBoxShape(btVector3(transform.scale.x(), transform.scale.y(), transform.scale.z()));
			}
			else if (physics.collisionShape == tMesh) {

				std::vector<glm::vec3>& vertices = render.mesh->vertices;

				// Fuite de mémoire ici, à corriger ASAP
				//std::shared_ptr<btTriangleMesh> tMesh(new btTriangleMesh());
				btTriangleMesh* tMesh = new btTriangleMesh();

				float sx = transform.scale.x();
				float sy = transform.scale.y();
				float sz = transform.scale.z();

				for (int i = 0; i < render.mesh->indices.size(); i+=3) {
					btVector3 v1 = btVector3(sx*vertices[i].x, sy*vertices[i].y, sz*vertices[i].z);
					btVector3 v2 = btVector3(sx*vertices[i+1].x, sy*vertices[i+1].y, sz*vertices[i+1].z);
					btVector3 v3 = btVector3(sx*vertices[i+2].x, sy*vertices[i+2].y, sz*vertices[i+2].z);
					tMesh->addTriangle(v1, v2, v3);
				}
				collisionShape = new btBvhTriangleMeshShape(tMesh, true);
			}/*
			else {
				std::vector<glm::vec3>& vertices = render.mesh->vertices;
				btConvexHullShape meshShape = btConvexHullShape();
				for (auto i = 0; i < vertices.size(); i++)
					meshShape.addPoint(btVector3(vertices[i].x, vertices[i].y, vertices[i].z));
				collisionShape = new btConvexHullShape(meshShape);
			}*/

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