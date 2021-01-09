#pragma once
#include "component.h"

// Include GLEW
#include <GL/glew.h>

class Render : public Component
{
public:
	Render();
	~Render();

	virtual bitmap getBitMap() const;
	static bitmap componentSignature;

	GLuint programID;
	std::string object_name;
};

