#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
public:
	Cube();

	void Init();
	void Update(float dt) override;
	void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
	GLuint shaderProgram = 0;
	MeshRenderer::ShaderProgram shader;

	// Configuracion cubo
	const float cubeSpeed = 1.f;
	const float maxAngle = 360.0f;
	const int vertexCount = 36;

	// Movimiento
	glm::vec3 forward = glm::vec3(0.f);
	glm::vec2 bounds = glm::vec2(0.f);
	glm::vec3 angle = glm::vec3(0.f);
};