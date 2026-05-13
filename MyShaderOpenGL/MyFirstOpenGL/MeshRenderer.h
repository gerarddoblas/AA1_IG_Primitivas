#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <glm.hpp>


class MeshRenderer
{
public:
	// Inicializamos con los vertices
	void Init(float* vertices, int byteSize);

	// Dibujamos usando un programa de shader y las matrices de transformacion
	void Draw(GLuint shaderProgram, const glm::mat4& translation, const glm::mat4& rotation, const glm::mat4& scale, const glm::mat4& view, const glm::mat4& projection, int vertexCount);

private:
	GLuint vao = 0;
	GLuint vbo = 0;
};
