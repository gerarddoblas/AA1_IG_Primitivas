#pragma once
#include "Primitive.h"
class Ortoedro : public Primitive
{

public:

	Ortoedro();

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

	float rotationZ = 0.0f;
	float timeAccumulator = 0.0f;

	const GLsizei vertexCount = 36;
	const float ortoedroWidth = 0.6f;
	const float ortoedroHeight = 1.6f;
	const float ortoedroScale = 0.7f;
	const float animSpeed = 2.0f;
	const float rotationSpeed = 50.0f;

	// Constants para el sin
	const float waveOffset = 1.0f;
	const float waveScale = 2.0f;
};

