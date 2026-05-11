#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


class MeshRenderer
{
public:

	struct ShaderProgram
	{
		GLuint vertexShader   = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;
	};

	
	void Init(float* vertices, int byteSize);

	
	void Draw(int vertexCount);

	// Cargamos y compilamos los shaders desde archivo
	GLuint LoadVertexShader(const std::string& filePath);
	GLuint LoadFragmentShader(const std::string& filePath);
	GLuint LoadGeometryShader(const std::string& filePath);

	// Enlazamos los shaders en un programa de GPU
	GLuint CreateProgram(const ShaderProgram& shaders);

	// Leemos el contenido de un archivo de texto
	std::string LoadFile(const std::string& filePath);

private:
	GLuint vao = 0;
	GLuint vbo = 0;
};
