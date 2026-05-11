#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "Ortoedro.h"
#include "Cube.h"
#include "Camera.h"
#include "Pyramid.h"
#include <vector>
#include "InputManager.h"
#include "Rendermanager.h"

const float SPEED_MULTIPLIER_UP = 1.1f;
const float SPEED_MULTIPLIER_DOWN = 0.9f;

enum PrimitiveType
{
	CUBE,
	ORTOEDRO,
	PYRAMID
};

void main()
{
	srand(time(NULL));
	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	//Inizializo el RenderManager
	RM->Init();

	//Inizializo el InputManager
	IM->Init(RM->GetWindow());

	std::vector<GameObject*> _gameObjects;

	Camera camera;

	//Inicializando el mapa
	_gameObjects.push_back(new Cube());/* [PrimitiveType::CUBE] = new Cube();*/
	/*_gameObjects[PrimitiveType::ORTOEDRO] = new Ortoedro();
	_gameObjects[PrimitiveType::PYRAMID] = new Pyramid();*/

	float lastFrame = 0.0f;

		//Generamos el game loop
		while (!IM->Listen()) {

			float currentFrame = (float)glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			//Cambiar a TimeManager
			if (!IM->GetKey(GLFW_KEY_SPACE, HOLD))
			{
				for (short i = _gameObjects.size() - 1; i >= 0; i--)
					_gameObjects[i]->Update(deltaTime);
			}

			

			//Genero matriz de vista
			//Cambiar a clase camara
			glm::mat4 viewMatrix = camera.GetViewMatrix();
			glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

			RM->ClearScreen();

			//Cambiar al RenderManager
			for (short i = _gameObjects.size() - 1; i >= 0; i--)
			{
				if(_gameObjects[i]->isVisible)
					_gameObjects[i]->Render(viewMatrix, projectionMatrix);
			}

			RM->RenderScreen();
		}

		for (short i = _gameObjects.size() - 1; i >= 0; i--)
			delete _gameObjects[i];

		_gameObjects.clear();

		RM->Release();

		glfwTerminate();
}