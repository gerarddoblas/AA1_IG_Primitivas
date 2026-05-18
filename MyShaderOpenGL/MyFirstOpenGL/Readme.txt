============================================================
PROYECTO: PRIMITIVAS OPENGL - MOTOR DE VIDEOJUEGOS
============================================================

ANEXO: CÓDIGO FUENTE REFACTORIZADO/GENERADO POR IA

--- Scene.h ---
#pragma once
#include <vector>
#include <glm.hpp>
#include "GameObject.h"

class Scene {
protected:
	std::vector<GameObject*> objects;
	std::vector<GameObject*> ui;

public:
	Scene() = default;
	virtual ~Scene() { OnExit(); }
	virtual void OnEnter() = 0;
	virtual void OnExit() {
		for (GameObject* o : objects) delete o;
		objects.clear();
	}
	virtual void Update(float dt) {
		for (int i = objects.size() - 1; i >= 0; i--) {
			if (objects[i]->isPendingDestroy) {
				delete objects[i];
				objects.erase(objects.begin() + i);
			}
		}
		for (GameObject* o : objects) if (o && o->isVisible) o->Update(dt);
	}
	virtual void Render(const glm::mat4& v, const glm::mat4& p) {
		for (GameObject* o : objects) if (o && o->isVisible) o->Render(v, p);
	}
	void AddGameObject(GameObject* obj) { if (obj) objects.push_back(obj); }
	std::vector<GameObject*>& GetObjects() { return objects; }
};

--- SceneManager.h ---
#pragma once
#include <unordered_map>
#include <string>
#include "Scene.h"
#define SM SceneManager::Instance()

class SceneManager {
private:
	std::unordered_map<std::string, Scene*> scenes;
	Scene* currentScene = nullptr;
	std::string nextScene = "";
public:
	static SceneManager& Instance() { static SceneManager sm; return sm; }
	bool AddScene(std::string n, Scene* s) { scenes[n] = s; return true; }
	bool InitFirstScene(std::string n) { currentScene = scenes[n]; if(currentScene) currentScene->OnEnter(); return true; }
	Scene* GetCurrentScene() const { return currentScene; }
	void UpdateCurrentScene(float dt) {
		if (nextScene != "") {
			if (currentScene) currentScene->OnExit();
			currentScene = scenes[nextScene];
			currentScene->OnEnter();
			nextScene = "";
		}
		if (currentScene) currentScene->Update(dt);
	}
};

--- Transform.cpp ---
#include "Transform.h"
#include <gtc/matrix_transform.hpp>

glm::mat4 Transform::GenerateScaleMatrix(glm::vec3 s) const { return glm::scale(glm::mat4(1.f), s); }
glm::mat4 Transform::GenerateRotationMatrix(glm::vec3 a, float d) const { return glm::rotate(glm::mat4(1.f), glm::radians(d), a); }
glm::mat4 Transform::GenerateTranslationMatrix(glm::vec3 t) const { return glm::translate(glm::mat4(1.f), t); }
glm::mat4 Transform::GetTranslationMatrix() const { return GenerateTranslationMatrix(position); }
glm::mat4 Transform::GetRotationMatrix() const {
	glm::mat4 r = GenerateRotationMatrix(glm::vec3(1,0,0), rotation.x);
	r = glm::rotate(r, glm::radians(rotation.y), glm::vec3(0,1,0));
	r = glm::rotate(r, glm::radians(rotation.z), glm::vec3(0,0,1));
	return r;
}
glm::mat4 Transform::GetScaleMatrix() const { return GenerateScaleMatrix(scale); }
glm::mat4 Transform::GetModelMatrix() const { return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix(); }

--- MeshRenderer.cpp ---
#include "MeshRenderer.h"
#include <gtc/type_ptr.hpp>

void MeshRenderer::Draw(GLuint shader, const glm::mat4& t, const glm::mat4& r, const glm::mat4& s, const glm::mat4& v, const glm::mat4& p, int count) {
	glUseProgram(shader);
	glUniformMatrix4fv(glGetUniformLocation(shader, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(t));
	glUniformMatrix4fv(glGetUniformLocation(shader, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(r));
	glUniformMatrix4fv(glGetUniformLocation(shader, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(s));
	glUniformMatrix4fv(glGetUniformLocation(shader, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(v));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(p));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, count);
	glBindVertexArray(0);
}

--- Source.cpp (Game Loop) ---
while (!IM->Listen()) {
    TIME.Update();
    if (!_isPaused) {
        if (IM->GetKey(GLFW_KEY_M, DOWN)) TIME.SetTimeMultiplier(TIME.GetTimeMultiplier() * 1.1f);
        if (IM->GetKey(GLFW_KEY_N, DOWN)) TIME.SetTimeMultiplier(TIME.GetTimeMultiplier() * 0.9f);
        if (IM->GetKey(GLFW_KEY_1, DOWN)) RM->ToggleWireframe();
        SM.UpdateCurrentScene(TIME.GetDeltaTime());
    }
    RM->ClearScreen();
    if (SM.GetCurrentScene()) SM.GetCurrentScene()->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(aspect));
    RM->RenderScreen();
}
============================================================
