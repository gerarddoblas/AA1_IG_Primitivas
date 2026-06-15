#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

#include "InputManager.h"
#include "Rendermanager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "MainScene.h"
#include "Camera.h"

void main()
{
	srand(time(NULL));

	// Inicializamos GLFW
	glfwInit();

	// Inizializo el RenderManager
	RM->Init();

	// Inizializo el InputManager
	IM->Init(RM->GetWindow());

	// Creamos la cámara y la escena principal
	Camera camera;
	SM.AddScene("Main", new MainScene());
	SM.InitFirstScene("Main");

	bool _isPaused = false;
	float lastFrame = 0.0f;

	// Generamos el game loop
	while (!IM->Listen()) {

		float currentFrame = (float)glfwGetTime();
		float deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Control de pausa
		if (IM->GetKey(GLFW_KEY_SPACE, DOWN))
			_isPaused = !_isPaused;

		TIME.Update();

		if (!_isPaused) {
			// Inputs de velocidad (M: +10%, N: -10%)
			if (IM->GetKey(GLFW_KEY_M, DOWN)) TIME.SetTimeMultiplier(TIME.GetTimeMultiplier() * 1.1f);
			if (IM->GetKey(GLFW_KEY_N, DOWN)) TIME.SetTimeMultiplier(TIME.GetTimeMultiplier() * 0.9f);

			// Input de Wireframe (Tecla 1)
			if (IM->GetKey(GLFW_KEY_1, DOWN)) RM->ToggleWireframe();

			// Inputs de visibilidad (2: Cubo, 3: Ortoedro, 4: Pirámide)
			if (SM.GetCurrentScene()) {
				auto& objects = SM.GetCurrentScene()->GetObjects();
				if (IM->GetKey(GLFW_KEY_2, DOWN) && objects.size() > 0) objects[0]->isVisible = !objects[0]->isVisible;
				if (IM->GetKey(GLFW_KEY_3, DOWN) && objects.size() > 1) objects[1]->isVisible = !objects[1]->isVisible;
				if (IM->GetKey(GLFW_KEY_4, DOWN) && objects.size() > 2) objects[2]->isVisible = !objects[2]->isVisible;
			}
			
			// Actualizamos el SceneManager
			SM.UpdateCurrentScene(TIME.GetDeltaTime());
		}

		RM->Update(TIME.GetDeltaTime());

		// Generamos matrices de cámara
		glm::mat4 viewMatrix = camera.GetViewMatrix();
		glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

		// Dibujado
		RM->ClearScreen();

		// El SceneManager renderiza
		if (SM.GetCurrentScene()) {
			SM.GetCurrentScene()->Render(viewMatrix, projectionMatrix);
		}

		RM->RenderScreen();
	}

	RM->Release();
	glfwTerminate();
}