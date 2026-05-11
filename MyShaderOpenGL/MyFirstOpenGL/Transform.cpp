#include "Transform.h"


glm::mat4 Transform::GenerateScaleMatrix(glm::vec3 scaleAxis) const
{
	return glm::scale(glm::mat4(1.0f), scaleAxis);
}


glm::mat4 Transform::GenerateRotationMatrix(glm::vec3 axis, float degrees) const
{
	return glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::normalize(axis));
}


glm::mat4 Transform::GenerateTranslationMatrix(glm::vec3 translation) const
{
	return glm::translate(glm::mat4(1.0f), translation);
}

glm::mat4 Transform::GetModelMatrix() const
{
	glm::mat4 t  = GenerateTranslationMatrix(position);
	glm::mat4 rx = GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), rotation.x);
	glm::mat4 ry = GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), rotation.y);
	glm::mat4 rz = GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), rotation.z);
	glm::mat4 s  = GenerateScaleMatrix(scale);

	return t * rx * ry * rz * s;
}
