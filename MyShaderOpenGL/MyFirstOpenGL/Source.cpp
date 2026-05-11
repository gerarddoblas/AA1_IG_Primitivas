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
#include <unordered_map>
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

	std::unordered_map<PrimitiveType, Primitive*> primitives;

	Camera camera;

	//Inicializando el mapa
	primitives[PrimitiveType::CUBE] = new Cube();
	primitives[PrimitiveType::ORTOEDRO] = new Ortoedro();
	primitives[PrimitiveType::PYRAMID] = new Pyramid();

	float lastFrame = 0.0f;

		//Generamos el game loop
		while (!IM->Listen()) {

			float currentFrame = (float)glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			//Cambiar a InputManager
			if (!IM->GetKey(GLFW_KEY_SPACE, HOLD))
			{
				for (std::unordered_map<PrimitiveType, Primitive*>::iterator it = primitives.begin(); it != primitives.end(); it++)
					it->second->Update(deltaTime);
			}

			//Cambiar al Update del RM
			if (IM->GetKey(GLFW_KEY_1, HOLD))
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//Genero matriz de vista
			//Cambiar a clase camara
			glm::mat4 viewMatrix = camera.GetViewMatrix();
			glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

			RM->ClearScreen();

			//Cambiar al RenderManager
			for (std::unordered_map<PrimitiveType, Primitive*>::iterator it = primitives.begin(); it != primitives.end(); it++)
			{
				if(it->second->isVisible)
					it->second->Render(viewMatrix, projectionMatrix);
			}

			RM->RenderScreen();
		}

		for (std::unordered_map<PrimitiveType, Primitive*>::iterator it = primitives.begin(); it != primitives.end(); it++)
			delete it->second;

		primitives.clear();

		RM->Release();

		glfwTerminate();
}