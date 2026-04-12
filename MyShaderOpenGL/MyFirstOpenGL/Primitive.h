#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class Primitive
{
public:

	struct ShaderProgram
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;
	};

	static std::string Load_File(const std::string& filePath);
	static GLuint LoadVertexShader(const std::string& filePath);
	static GLuint LoadFragmentShader(const std::string& filePath);
	static GLuint LoadGeometryShader(const std::string& filePath);
	static GLuint CreateProgram(const ShaderProgram& shaders);

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Input() = 0;
};

