#pragma once

#include "Vertex.h"
#include "GLSLProgram.h"
#include "Texture.h"

class Cube
{
	GLuint m_VBO; //Vertex Buffer Object
	GLuint m_VAO; //Vertex Array Object
	GLuint m_EBO; //Element array
	Vertex3D m_Vertices[12];
	Texture* m_Texture;

public:
	Cube(Texture* texture);
	~Cube();
	void Init(Engine::GLSLProgram * shaderProgram);
	void draw();
};

