#include "GameObject.h"

// Creamos para el gameObject no de error
GameObject::GameObject()
{
	transform = new Transform();
	meshRenderer = new MeshRenderer();
}

// No memory leak
GameObject::~GameObject()
{
	delete transform;
	delete meshRenderer;
}
