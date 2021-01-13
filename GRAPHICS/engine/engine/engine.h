// engine.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets.

#pragma once

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/tangentspace.hpp>
#include <common/PlanetMaker.h>

using namespace std;

GLuint VertexArrayID;
GLuint programID;
GLuint LightID;

GLuint MatrixID;
GLuint ViewMatrixID;
GLuint ModelMatrixID;
GLuint ModelView3x3MatrixID;

GLuint DiffuseTexture;
GLuint NormalTexture;
GLuint SpecularTexture;

GLuint DiffuseTextureID;
GLuint NormalTextureID;
GLuint SpecularTextureID;

vector<vec3> vertices;
vector<vec2> uvs;
vector<vec3> normals;
vector<vec3> tangents;
vector<vec3> bitangents;

vector<unsigned short> indices;
vector<vec3> indexed_vertices;
vector<vec2> indexed_uvs;
vector<vec3> indexed_normals;
vector<vec3> indexed_tangents;
vector<vec3> indexed_bitangents;

GLuint vertexbuffer;
GLuint uvbuffer;
GLuint normalbuffer;
GLuint tangentbuffer;
GLuint bitangentbuffer;
GLuint elementbuffer;

// For speed computation
double lastTime = glfwGetTime();
int nbFrames = 0;
vec3 lightPos;

bool InitGLFW() {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // So that glBegin/glVertex/glEnd work

	return true;
}

bool InitWindow() {
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Graphics test", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	return true;
}

bool InitGLEW() {
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return false;
	}

	return true;
}

bool Init() {
	return InitGLFW() && InitWindow() && InitGLEW();
}

void ParamAndID() {
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders("NormalMapping.vertexshader", "NormalMapping.fragmentshader");

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");
	ViewMatrixID = glGetUniformLocation(programID, "V");
	ModelMatrixID = glGetUniformLocation(programID, "M");
	ModelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");

	// Get a handle for our "myTextureSampler" uniform
	DiffuseTextureID = glGetUniformLocation(programID, "DiffuseTextureSampler");
	NormalTextureID = glGetUniformLocation(programID, "NormalTextureSampler");
	SpecularTextureID = glGetUniformLocation(programID, "SpecularTextureSampler");
}

glm::vec3 transform(Vector3 vec) {
	glm::vec3 temp = glm::vec3();
	temp.x = vec.x; temp.y = vec.y; temp.z = vec.z;
	return temp;
}

void loadPlanet(PlanetMaker pm) {

	for (int i = 0; i < 6; ++i) {
		Mesh mesh = pm.getPlanetFace(i).getMesh();

		for (int j = 0; j < mesh.triangles.size(); j += 3) {
			for (int k = 0; k < 3; k++) {

				int t = mesh.triangles.at(j + k);

				vertices.push_back(transform(mesh.vertices.at(t)));
				normals.push_back(transform(mesh.normals.at(t)));
				uvs.push_back(glm::vec2(0.0f));

			}
		}
	}
}

void OBJReader(string path) {

	// Load the texture
	DiffuseTexture = loadDDS(string(path + "diffuse.DDS").c_str());
	NormalTexture = loadBMP_custom(string(path + "normal.bmp").c_str());
	SpecularTexture = loadDDS(string(path + "specular.DDS").c_str());

	// Read our .obj file
	loadOBJ(string(path + "object.obj").c_str(), vertices, uvs, normals);
	
	// Generate planet
	PlanetMaker pm = PlanetMaker(Vector3::zero, 10);
	//loadPlanet(pm);

	computeTangentBasis(
		vertices, uvs, normals, // input
		tangents, bitangents    // output
	);

	indexVBO_TBN(
		vertices, uvs, normals, tangents, bitangents,
		indices, indexed_vertices, indexed_uvs, indexed_normals, indexed_tangents, indexed_bitangents
	);
}

void VBOLoader() {
	// Load it into a VBO

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(vec3), &indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &tangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_tangents.size() * sizeof(vec3), &indexed_tangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &bitangentbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_bitangents.size() * sizeof(vec3), &indexed_bitangents[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}

void ComputeAndShare() {

	// Compute the MVP matrix from keyboard and mouse input
	computeMatricesFromInputs();
	glm::mat4 ProjectionMatrix = getProjectionMatrix();
	glm::mat4 ViewMatrix = getViewMatrix();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix3fv(ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);
}

void Binding() {
	// Bind our diffuse texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, DiffuseTexture);
	// Set our "DiffuseTextureSampler" sampler to use Texture Unit 0
	glUniform1i(DiffuseTextureID, 0);

	// Bind our normal texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, NormalTexture);
	// Set our "NormalTextureSampler" sampler to use Texture Unit 1
	glUniform1i(NormalTextureID, 1);

	// Bind our specular texture in Texture Unit 2
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, SpecularTexture);
	// Set our "SpecularTextureSampler" sampler to use Texture Unit 2
	glUniform1i(SpecularTextureID, 2);
}

void AttributeAndDraw() {
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 4th attribute buffer : tangents
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
	glVertexAttribPointer(
		3,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 5th attribute buffer : bitangents
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
	glVertexAttribPointer(
		4,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
}

void Clean() {
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &tangentbuffer);
	glDeleteBuffers(1, &bitangentbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &DiffuseTexture);
	glDeleteTextures(1, &NormalTexture);
	glDeleteTextures(1, &SpecularTexture);
	glDeleteVertexArrays(1, &VertexArrayID);
}

int process(string path) {
	if (!Init()) return -1;
	ParamAndID();
	OBJReader(path);
	VBOLoader();

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	LightID = glGetUniformLocation(programID, "LightPosition_worldspace");


	do {

		// Measure speed
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
			// printf and reset
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		ComputeAndShare();

		lightPos = vec3(0, 0, 4);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

		Binding();
		AttributeAndDraw();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	Clean();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}