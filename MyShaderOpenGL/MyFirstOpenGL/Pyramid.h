#pragma once
#include "Primitive.h"

class Pyramid : public Primitive
{
public:

	Pyramid();

	void Init();
	void Update(float dt) override;
	void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
private:

	GLuint VAO, VBO;
	GLuint shaderProgram;
	ShaderProgram shader;

	const glm::vec3 pyramidPosition = glm::vec3(1.f, 0.0f, 0.0f);
	const glm::vec3 pyramidRotation = glm::vec3(0.0f, 0.0f, 0.0f);
	const glm::vec3 pyramidScale = glm::vec3(0.25f, 0.25f, 0.25f);
	const glm::vec3 pyramidForward = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec2 pyramidBounds = glm::vec2(1.f, -1.f);
	const glm::vec3 pyramidAngle = glm::vec3(50.0f, 50.0f, 0.0f);

	const float pyramidSpeed = 1.f;

	const float colorInterval = 2.0f;
	float colorTime = 0.0f;
	short colorIndex = 0;
};