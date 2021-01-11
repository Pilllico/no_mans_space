#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

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

#include "system.h"
#include "physicssystem.h"

using namespace std;

struct Textures {
	GLuint DiffuseTexture;
	GLuint NormalTexture;
	GLuint SpecularTexture;
};

struct Buffers {
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint tangentbuffer;
	GLuint bitangentbuffer;
	GLuint elementbuffer;
};

struct Mesh {
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
};

struct Object {
	Textures textures;

	Mesh mesh;

	Buffers buffers;
};

struct programData {
	GLuint LightID;

	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint ModelView3x3MatrixID;

	GLuint DiffuseTextureID;
	GLuint NormalTextureID;
	GLuint SpecularTextureID;
};

class renderSystem : public System
{
public:
    renderSystem();
	bool initialize();
    bool virtual execute();
	void setViewMatrix(glm::mat4 ViewMatrix);
	void Clean();
	GLuint getProgramID();
    ~renderSystem();
private:
	bool Init();
	bool InitGLFW();
	bool InitWindow();
	bool InitGLEW();
	void ParamAndID(string vertexShader, string fragmentShader);
	void OBJReader(string path, string name);
	void VBOLoader(string name);
	void ComputeAndShare(GLuint programID, const Transform& transfrom);
	void Binding(GLuint programID, string name);
	void AttributeAndDraw(string name);
	std::unordered_map<GLuint, programData> shaderData;
	std::unordered_map<string, Object> objects;
	vec3 lightPos;
	GLuint VertexArrayID;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
};

#endif // RENDERSYSTEM_H
