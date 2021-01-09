#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
 
// Include GLEW
#include <GL/glew.h>

#include <GLFW/glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/tangentspace.hpp>

#include "entitymanager.h"
#include "displaysystem.h"
#include "physicssystem.h"
#include "rendersystem.h"

int main(int argc, char *argv[])
{
	displaySystem displaySystem;
	physicsSystem physicsSystem;

	renderSystem renderSystem;
	renderSystem.initialize();

	Entity e1 = EntityManager::getInstance().createEntity();
	Entity e2 = EntityManager::getInstance().createEntity();

	EntityManager::getInstance().addComponentToEntity(e1, btVector3(0.0f, 20.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f), btVector3(1.0f, 1.0f, 1.0f));
	EntityManager::getInstance().addComponentToEntity(e2, btVector3(-1.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 45.0f), btVector3(1.0f, 1.0f, 1.0f));
	EntityManager::getInstance().addComponentToEntity(e1, 1.0f, Sphere);
	EntityManager::getInstance().addComponentToEntity(e2, 0.0f, Box);	

	EntityManager::getInstance().addComponentToEntity(e1, renderSystem.getProgramID(), "sphere");
	EntityManager::getInstance().addComponentToEntity(e2, renderSystem.getProgramID(), "cube");

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		displaySystem.execute();
		physicsSystem.execute();
		renderSystem.execute();
	}

	renderSystem.Clean();
	glfwTerminate();

	return 0;
}
