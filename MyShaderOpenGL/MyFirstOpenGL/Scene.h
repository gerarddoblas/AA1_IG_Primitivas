#pragma once
#include <vector>
#include <string>
#include <glm.hpp>
#include "GameObject.h"
#include "RenderManager.h"

class Scene {
protected:
	std::vector<GameObject*> objects;
	
	std::vector<GameObject*> ui;

public:
	Scene() = default;
	virtual ~Scene() {
		OnExit();
	}

	virtual void OnEnter() = 0;
	
	virtual void OnExit() {
		// Destruimos todos los objetos de la escena
		for (GameObject* o : objects) {
			delete o;
		}
		objects.clear();

		for (GameObject* o : ui) {
			delete o;
		}
		ui.clear();
	}

	virtual void Update(float dt) {
		// Control de destruccion de objetos
		for (int i = objects.size() - 1; i >= 0; i--) {
			if (objects[i]->isPendingDestroy) {
				delete objects[i];
				objects.erase(objects.begin() + i);
			}
		}

		// Actualizamos todos los objetos
		for (GameObject* o : objects) {
			if (o != nullptr && o->isVisible) {
				o->Update(dt);
			}
		}
	}

	virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
		// Le pidimos a cada objeto que se dibuje
		for (GameObject* o : objects) {
			if (o != nullptr && o->isVisible) {
				o->Render(viewMatrix, projectionMatrix);
			}
		}
	}

	// Metodo para añadir objetos a la escena
	void AddGameObject(GameObject* obj) {
		if (obj != nullptr) objects.push_back(obj);
	}

	std::vector<GameObject*>& GetObjects() { return objects; }
};
