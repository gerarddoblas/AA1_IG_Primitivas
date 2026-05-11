#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Transform
{
public:
	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 rotation = glm::vec3(0.f);
	glm::vec3 scale    = glm::vec3(1.f);

	glm::mat4 GetModelMatrix() const;

	// Matriz escalado
	glm::mat4 GenerateScaleMatrix(glm::vec3 scaleAxis) const;

	// Matriz rotacion
	glm::mat4 GenerateRotationMatrix(glm::vec3 axis, float degrees) const;

	// Matriz traslacion
	glm::mat4 GenerateTranslationMatrix(glm::vec3 translation) const;
};
