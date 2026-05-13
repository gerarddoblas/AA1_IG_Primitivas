#include "Transform.h"
#include <gtc/matrix_transform.hpp>

glm::mat4 Transform::GenerateScaleMatrix(glm::vec3 scaleAxis) const {
	return glm::scale(glm::mat4(1.0f), scaleAxis);
}

glm::mat4 Transform::GenerateRotationMatrix(glm::vec3 axis, float degrees) const {
	return glm::rotate(glm::mat4(1.0f), glm::radians(degrees), axis);
}

glm::mat4 Transform::GenerateTranslationMatrix(glm::vec3 translation) const {
	return glm::translate(glm::mat4(1.0f), translation);
}

glm::mat4 Transform::GetTranslationMatrix() const {
	return GenerateTranslationMatrix(position);
}

glm::mat4 Transform::GetRotationMatrix() const {
	glm::mat4 rx = GenerateRotationMatrix(glm::vec3(1, 0, 0), rotation.x);
	glm::mat4 ry = GenerateRotationMatrix(glm::vec3(0, 1, 0), rotation.y);
	glm::mat4 rz = GenerateRotationMatrix(glm::vec3(0, 0, 1), rotation.z);
	return rx * ry * rz;
}

glm::mat4 Transform::GetScaleMatrix() const {
	return GenerateScaleMatrix(scale);
}

glm::mat4 Transform::GetModelMatrix() const {
	return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
}
