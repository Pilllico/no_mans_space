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
	std::unordered_map<std::string, Mesh*> meshes;
	renderSystem.initialize(meshes);

	Entity planet1 = EntityManager::getInstance().createEntity();
	Entity planet2 = EntityManager::getInstance().createEntity();
	Entity body1 = EntityManager::getInstance().createEntity();
	Entity body2 = EntityManager::getInstance().createEntity();
	Entity player = EntityManager::getInstance().createEntity();

	EntityManager::getInstance().addComponentToEntity(planet1, btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f), btVector3(10.0f, 10.0f, 10.0f));
	EntityManager::getInstance().addComponentToEntity(planet2, btVector3(50.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f), btVector3(10.0f, 10.0f, 10.0f));
	EntityManager::getInstance().addComponentToEntity(body1, btVector3(25.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 45.0f), btVector3(1.0f, 1.0f, 1.0f));
	EntityManager::getInstance().addComponentToEntity(body2, btVector3(0.0f, 20.0f, 0.0f), btVector3(0.0f, 0.0f, 45.0f), btVector3(1.0f, 1.0f, 1.0f));
	EntityManager::getInstance().addComponentToEntity(player, btVector3(0.0f, 0.0f, 20.0f), btVector3(0.0f, 0.0f, 45.0f), btVector3(1.0f, 1.0f, 1.0f));

	EntityManager::getInstance().addComponentToEntity(planet1, renderSystem.getProgramID(), "suzanne", meshes.at("suzanne"));
	EntityManager::getInstance().addComponentToEntity(planet2, renderSystem.getProgramID(), "sphere", meshes.at("sphere"));
	EntityManager::getInstance().addComponentToEntity(body1, renderSystem.getProgramID(), "sphere", meshes.at("sphere"));
	EntityManager::getInstance().addComponentToEntity(body2, renderSystem.getProgramID(), "sphere", meshes.at("sphere"));
	EntityManager::getInstance().addComponentToEntity(player, renderSystem.getProgramID(), "sphere", meshes.at("sphere"));

	EntityManager::getInstance().addComponentToEntity(planet1, 0.0f, 9.81, tMesh);
	EntityManager::getInstance().addComponentToEntity(planet2, 0.0f, 9.81, Sphere);
	EntityManager::getInstance().addComponentToEntity(body1, 1.0f, 9.81, Sphere);
	EntityManager::getInstance().addComponentToEntity(body2, 1.0f, 9.81, Sphere);
	EntityManager::getInstance().addComponentToEntity(player, 1.0f, 9.81, Sphere);

	btRigidBody* controllerBody = physicsSystem.getData().at(player).second;

	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	
	float burstStrength = 0.2f;
	float mouseSpeed = 0.005f;

	double lastTime = glfwGetTime();

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0)
	{
		const Transform& transform = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")))->getTransform(player);
		glm::vec3 position = glm::vec3(transform.position.getX(), transform.position.getY(), transform.position.getZ());

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);

		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		// Reset mouse position for next frame
		glfwSetCursorPos(window, 1280 / 2, 720 / 2);

		// Compute new orientation
		horizontalAngle += mouseSpeed * float(1280 / 2 - xpos);
		verticalAngle += mouseSpeed * float(720 / 2 - ypos);

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
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			controllerBody->applyCentralImpulse(burstStrength * btVector3(direction.x, direction.y, direction.z));
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			controllerBody->applyCentralImpulse(-burstStrength * btVector3(direction.x, direction.y, direction.z));
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			controllerBody->applyCentralImpulse(burstStrength * btVector3(right.x, right.y, right.z));
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			controllerBody->applyCentralImpulse(-burstStrength * btVector3(right.x, right.y, right.z));
		}
		// Strafe up
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			controllerBody->applyCentralImpulse(burstStrength * btVector3(up.x, up.y, up.z));
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			controllerBody->applyCentralImpulse(-burstStrength * btVector3(up.x, up.y, up.z));
		}

		renderSystem.setViewMatrix(glm::lookAt(
			position,           // Camera is here
			position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		));

		// For the next frame, the "last time" will be "now"
		lastTime = currentTime;


		displaySystem.execute();
		physicsSystem.execute();
		renderSystem.execute();
	}

	renderSystem.Clean();
	glfwTerminate();

	return 0;
}
