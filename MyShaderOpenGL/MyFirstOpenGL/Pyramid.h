#pragma once
#include "Primitive.h"

class Pyramid : public Primitive
{
public:

	Pyramid();

	void Init();
	void Update(float dt) override;
	void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
	void Input(GLFWwindow* window) override;
private:

	GLuint VAO, VBO;
	GLuint shaderProgram;
	ShaderProgram shader;

	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 rotation = glm::vec3(0.f);
	glm::vec3 scale = glm::vec3(1.f);

	float rotationX = 0.0f;
	float rotationY = 0.0f;
};