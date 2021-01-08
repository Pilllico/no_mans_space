#include "entitymanager.h"
#include "displaysystem.h"
#include "physicssystem.h"
#include <iostream>

int main(int argc, char *argv[])
{
	displaySystem displaySystem;
	physicsSystem physicsSystem;

	Entity e1 = EntityManager::getInstance().createEntity();
	Entity e2 = EntityManager::getInstance().createEntity();

	EntityManager::getInstance().addComponentToEntity(e1, btVector3(0.0f, 20.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f), btVector3(2.0f, 2.0f, 2.0f));
	EntityManager::getInstance().addComponentToEntity(e2, btVector3(-1.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 45.0f), btVector3(1.0f, 1.0f, 1.0f));
	EntityManager::getInstance().addComponentToEntity(e1, 1.0f, Sphere);
	EntityManager::getInstance().addComponentToEntity(e2, 0.0f, Box);	

	while (true)
	{
		displaySystem.execute();
		physicsSystem.execute();
	}

	return 0;
}
