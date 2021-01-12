#include "rendersystem.h"

extern GLFWwindow* window;

renderSystem::renderSystem()
{
	systemSignature = bitmap("00000011");
	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 500.0f);
}

bool renderSystem::initialize(std::unordered_map<std::string, Mesh*>& meshes)
{
	if (!Init())
		return false;

	ParamAndID("../NormalMapping.vertexshader", "../NormalMapping.fragmentshader");
	OBJReader("../objects/sphere/", "sphere");
	VBOLoader("sphere");
	meshes.insert(std::make_pair("sphere", &objects.at("sphere").mesh));
	OBJReader("../objects/cube/", "cube");
	VBOLoader("cube");
	meshes.insert(std::make_pair("cube", &objects.at("cube").mesh));
	OBJReader("../objects/suzanne/", "suzanne");
	VBOLoader("suzanne");
	meshes.insert(std::make_pair("suzanne", &objects.at("suzanne").mesh));

	/*for (auto pair : objects) {
		meshes.insert(std::make_pair(pair.first, &pair.second.mesh));
	}*/

	return true;
}

renderSystem::~renderSystem()
{
   
}

bool renderSystem::InitGLFW()
{
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

bool renderSystem::InitWindow()
{
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Game Engine", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	return true;
}

bool renderSystem::InitGLEW()
{
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return false;
	}

	return true;
}

void renderSystem::ParamAndID(string vertexShader, string fragmentShader)
{
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
	GLuint programID = LoadShaders(vertexShader.c_str(), fragmentShader.c_str());

	programData IDs;

	// Get a handle for our "MVP" uniform
	IDs.MatrixID = glGetUniformLocation(programID, "MVP");
	IDs.ViewMatrixID = glGetUniformLocation(programID, "V");
	IDs.ModelMatrixID = glGetUniformLocation(programID, "M");
	IDs.ModelView3x3MatrixID = glGetUniformLocation(programID, "MV3x3");

	// Get a handle for our "myTextureSampler" uniform
	IDs.DiffuseTextureID = glGetUniformLocation(programID, "DiffuseTextureSampler");
	IDs.NormalTextureID = glGetUniformLocation(programID, "NormalTextureSampler");
	IDs.SpecularTextureID = glGetUniformLocation(programID, "SpecularTextureSampler");

	IDs.LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

	shaderData.insert(std::make_pair(programID, IDs));
}

void renderSystem::OBJReader(string path, string name)
{
	objects.insert(std::make_pair(name, Object()));

	// Load the texture
	objects.at(name).textures.DiffuseTexture = loadDDS(string(path + "diffuse.DDS").c_str());
	objects.at(name).textures.NormalTexture = loadBMP_custom(string(path + "normal.bmp").c_str());
	objects.at(name).textures.SpecularTexture = loadDDS(string(path + "specular.DDS").c_str());

	// Read our .obj file
	loadOBJ(string(path + "object.obj").c_str(), objects.at(name).mesh.vertices, objects.at(name).mesh.uvs, objects.at(name).mesh.normals);

	computeTangentBasis(
		objects.at(name).mesh.vertices, objects.at(name).mesh.uvs, objects.at(name).mesh.normals, // input
		objects.at(name).mesh.tangents, objects.at(name).mesh.bitangents    // output
	);

	indexVBO_TBN(
		objects.at(name).mesh.vertices, objects.at(name).mesh.uvs, objects.at(name).mesh.normals, objects.at(name).mesh.tangents, objects.at(name).mesh.bitangents,
		objects.at(name).mesh.indices, objects.at(name).mesh.indexed_vertices, objects.at(name).mesh.indexed_uvs, objects.at(name).mesh.indexed_normals, objects.at(name).mesh.indexed_tangents, objects.at(name).mesh.indexed_bitangents
	);
}

void renderSystem::VBOLoader(string name)
{
	// Load it into a VBO

	GLuint& vertexbuffer = objects.at(name).buffers.vertexbuffer;
	const vector<vec3>& indexed_vertices = objects.at(name).mesh.indexed_vertices;
	
	GLuint& uvbuffer = objects.at(name).buffers.uvbuffer;
	const vector<vec2>& indexed_uvs = objects.at(name).mesh.indexed_uvs;

	GLuint& normalbuffer = objects.at(name).buffers.normalbuffer;
	const vector<vec3>& indexed_normals = objects.at(name).mesh.indexed_normals;

	GLuint& tangentbuffer = objects.at(name).buffers.tangentbuffer;
	const vector<vec3>& indexed_tangents = objects.at(name).mesh.indexed_tangents;

	GLuint& bitangentbuffer = objects.at(name).buffers.bitangentbuffer;
	const vector<vec3>& indexed_bitangents = objects.at(name).mesh.indexed_bitangents;

	GLuint& elementbuffer = objects.at(name).buffers.elementbuffer;
	const vector<unsigned short>& indices = objects.at(name).mesh.indices;

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

void renderSystem::ComputeAndShare(GLuint programID, const Transform& transform)
{
	// Compute the MVP matrix from keyboard and mouse input
	computeMatricesFromInputs();
	//glm::mat4 ProjectionMatrix = getProjectionMatrix();
	//glm::mat4 ViewMatrix = getViewMatrix();

	glm::mat4 ModelMatrix = glm::mat4(1.0);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(transform.position.getX(), transform.position.getY(), transform.position.getZ()));

	// Faux, à corriger avec les angles d'euler, pas les bon angles actuellement
	ModelMatrix = glm::rotate(ModelMatrix, transform.rotation.getX(), glm::vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, transform.rotation.getY(), glm::vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, transform.rotation.getZ(), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(transform.scale.getX(), transform.scale.getY(), transform.scale.getZ()));
	glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(shaderData.at(programID).MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(shaderData.at(programID).ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(shaderData.at(programID).ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(shaderData.at(programID).ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix3fv(shaderData.at(programID).ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);
}

void renderSystem::Binding(GLuint programID, string name)
{
	// Bind our diffuse texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, objects.at(name).textures.DiffuseTexture);
	// Set our "DiffuseTextureSampler" sampler to use Texture Unit 0
	glUniform1i(shaderData.at(programID).DiffuseTextureID, 0);

	// Bind our normal texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, objects.at(name).textures.NormalTexture);
	// Set our "NormalTextureSampler" sampler to use Texture Unit 1
	glUniform1i(shaderData.at(programID).NormalTextureID, 1);

	// Bind our specular texture in Texture Unit 2
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, objects.at(name).textures.SpecularTexture);
	// Set our "SpecularTextureSampler" sampler to use Texture Unit 2
	glUniform1i(shaderData.at(programID).SpecularTextureID, 2);
}

void renderSystem::AttributeAndDraw(string name)
{
	GLuint vertexbuffer = objects.at(name).buffers.vertexbuffer;
	GLuint uvbuffer = objects.at(name).buffers.uvbuffer;
	GLuint normalbuffer = objects.at(name).buffers.normalbuffer;
	GLuint tangentbuffer = objects.at(name).buffers.tangentbuffer;
	GLuint bitangentbuffer = objects.at(name).buffers.bitangentbuffer;
	GLuint elementbuffer = objects.at(name).buffers.elementbuffer;
	const vector<unsigned short>& indices = objects.at(name).mesh.indices;

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

void renderSystem::Clean()
{
	std::unordered_map<GLuint, programData> shaderData;
	std::unordered_map<string, Object> objects;

	for (auto pair : shaderData) {
		glDeleteProgram(pair.first);
	}

	for (auto pair : objects) {
		
		GLuint vertexbuffer = pair.second.buffers.vertexbuffer;
		GLuint uvbuffer = pair.second.buffers.uvbuffer;
		GLuint normalbuffer = pair.second.buffers.normalbuffer;
		GLuint tangentbuffer = pair.second.buffers.tangentbuffer;
		GLuint bitangentbuffer = pair.second.buffers.bitangentbuffer;
		GLuint elementbuffer = pair.second.buffers.elementbuffer;

		GLuint DiffuseTexture = pair.second.textures.DiffuseTexture;
		GLuint NormalTexture = pair.second.textures.NormalTexture;
		GLuint SpecularTexture = pair.second.textures.SpecularTexture;

		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteBuffers(1, &normalbuffer);
		glDeleteBuffers(1, &tangentbuffer);
		glDeleteBuffers(1, &bitangentbuffer);
		glDeleteBuffers(1, &elementbuffer);

		glDeleteTextures(1, &DiffuseTexture);
		glDeleteTextures(1, &NormalTexture);
		glDeleteTextures(1, &SpecularTexture);
	}

	glDeleteVertexArrays(1, &VertexArrayID);
}

GLuint renderSystem::getProgramID()
{
	return shaderData.begin()->first;
}

bool renderSystem::execute()
{
	TransformManager* transformManager = dynamic_cast<TransformManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("1")));
	RenderManager* renderManager = dynamic_cast<RenderManager*>(EntityManager::getInstance().getComponentManagerForSystem(bitmap("10")));

	const std::unordered_map<Entity, Render, EntityHasher>& renders = renderManager->getAllRenders();
	const std::unordered_map<Entity, Transform, EntityHasher>& transforms = transformManager->getAllTransforms();

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (Entity e : entityList)
	{
		const Render& render = renders.at(e);
		GLuint programID = render.programID;

		glUseProgram(programID);

		//GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

		ComputeAndShare(programID, transforms.at(e));

		lightPos = vec3(0, 0, 50);
		glUniform3f(shaderData.at(programID).LightID, lightPos.x, lightPos.y, lightPos.z);

		Binding(programID, render.object_name);
		AttributeAndDraw(render.object_name);
	}

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();

	return true;
}

void renderSystem::setViewMatrix(glm::mat4 ViewMatrix)
{
	this->ViewMatrix = ViewMatrix;
}

bool renderSystem::Init()
{
	return InitGLFW() && InitWindow() && InitGLEW();
}
