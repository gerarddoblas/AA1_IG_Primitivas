#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camera {
public:
	glm::vec3 position = glm::vec3(2.0f, 2.0f, 3.0f);
	glm::vec3 localVectorUp = glm::vec3(0.f, 1.f, 0.f);

	float fFov = 45.f;
	float fnear = 0.1f;
	float fFar = 10.f;

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix(float aspectRatio) const;
};