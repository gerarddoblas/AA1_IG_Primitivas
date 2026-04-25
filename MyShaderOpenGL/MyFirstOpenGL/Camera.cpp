#include "Camera.h"

glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(position, glm::vec3(0.5f, 0.5f, 0.0f), localVectorUp);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const {
	return glm::perspective(glm::radians(fFov), aspectRatio, fnear, fFar);
}
