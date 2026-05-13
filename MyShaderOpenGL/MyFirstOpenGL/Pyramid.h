#pragma once
#include "GameObject.h"
#define NUM_COLORS 3

class Pyramid : public GameObject
{
public:
	Pyramid();

	void Init();
	void Update(float dt) override;
	void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
	GLuint shaderProgram = 0;

	// Propiedades de movimiento
	glm::vec3 forward = glm::vec3(0.f);
	glm::vec2 bounds  = glm::vec2(0.f);
	glm::vec3 angle   = glm::vec3(0.f);

	// Propiedades de color ciclico
	float colorTime  = 0.0f;
	short colorIndex = 0;

	// Constantes de configuracion
	const float pyramidSpeed = 1.f;
	const float colorInterval = 2.0f;
	const float maxAngle = 360.0f;
	const int vertexCount = 18;
};