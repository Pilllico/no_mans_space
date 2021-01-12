#pragma once
#include "component.h"

// Include GLEW
#include <GL/glew.h>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Mesh {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	std::vector<unsigned short> indices;
	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;
	std::vector<glm::vec3> indexed_tangents;
	std::vector<glm::vec3> indexed_bitangents;
};

class Render : public Component
{
public:
	Render();
	~Render();

	virtual bitmap getBitMap() const;
	static bitmap componentSignature;

	GLuint programID;
	std::string object_name;
	Mesh* mesh;
};

