#pragma once
#include <glm.hpp>
#include "Transform.h"
#include "MeshRenderer.h"

class GameObject
{
protected:
	Transform* transform = nullptr;
	MeshRenderer* meshRenderer = nullptr;

public:
	bool isVisible = true;
	float speed = 1.0f;
	bool isPendingDestroy = false;

	GameObject();
	virtual ~GameObject();

	virtual void Update(float dt) = 0;

	virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) = 0;

	Transform* GetTransform() const { return transform; }
	MeshRenderer* GetMeshRenderer() const { return meshRenderer; }
};
