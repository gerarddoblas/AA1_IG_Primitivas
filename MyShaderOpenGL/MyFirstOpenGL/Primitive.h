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

	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 rotation = glm::vec3(0.f);
	glm::vec3 scale = glm::vec3(1.f);

	glm::vec3 forward = glm::vec3(0.f, 0.f, 0.f);
	glm::vec2 bounds = glm::vec2(0.f, 0.f);
	glm::vec3 angle = glm::vec3(0.f, 0.f, 0.f);

	float speed = 0.0f;
	bool isVisible = true;

	//Funcion que genera una matriz de escalado representada por un vector
	virtual glm::mat4 GenerateScaleMatrix(glm::vec3 scaleAxis);

	//Funcion que genera una matriz de rotacion dado un angulo y un vector
	virtual glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float fDegrees);

	//Funcion que genera una matriz de traslacion representada por un vector
	virtual glm::mat4 GenerateTranslationMatrix(glm::vec3 translation);

	virtual std::string Load_File(const std::string& filePath);
	virtual GLuint LoadVertexShader(const std::string& filePath);
	virtual GLuint LoadFragmentShader(const std::string& filePath);
	virtual GLuint LoadGeometryShader(const std::string& filePath);
	virtual GLuint CreateProgram(const ShaderProgram& shaders);

	virtual void Update(float dt) = 0;
	virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;
};