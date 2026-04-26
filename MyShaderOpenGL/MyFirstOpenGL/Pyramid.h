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
};