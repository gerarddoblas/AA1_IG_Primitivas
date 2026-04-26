#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Ortoedro.h"
#include "Cube.h"
#include "Camera.h"
#include "Pyramid.h"

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

void ProcessInput(GLFWwindow* window, bool& isPaused, bool& spacePressed, bool& isWireframe, bool& key1Pressed, bool& renderCube, bool&key2Pressed, bool& renderOrtoedro, bool& key3Pressed) {
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (!spacePressed) {
			isPaused = !isPaused;
			spacePressed = true;
		}
	}
	else {
		spacePressed = false;
	}

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		if (!key1Pressed) {
			isWireframe = !isWireframe;
			key1Pressed = true;
		}
	}
	else {
		key1Pressed = false;
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		if (!key2Pressed) {
			renderCube = !renderCube;
			key2Pressed = true;
		}
	}
	else {
		key2Pressed = false;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		if (!key3Pressed) {
			renderOrtoedro = !renderOrtoedro;
			key3Pressed = true;
		}
	}
	else {
		key3Pressed = false;
	}
}

void main()
{
	srand(time(NULL));
	//Inicializamos GLFW para gestionar ventanas e inputs
	glfwInit();

	
	//Configurar la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	//Asignamos función de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	//Permitimos a GLEW usar funcionalidades experimentales
	glewExperimental = GL_TRUE;

	//Activamos cull face
	glEnable(GL_CULL_FACE);

	//Indicamos lado del culling
	glCullFace(GL_FRONT);

	//Inicializamos GLEW y controlamos errores
	if (glewInit() == GLEW_OK) {

		//Definimos color para limpiar el buffer de color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		Cube cube;
		Ortoedro ortoedro;
		std::vector<Primitive*> primitives;

		primitives.push_back(new Ortoedro());
		primitives.push_back(new Pyramid());

		Camera camera;

		float lastFrame = 0.0f;
		bool isPaused = false;
		bool spacePressed = false;
		bool isWireframe = false;
		bool key1Pressed = false;
		bool renderOrtoedro = true;
		bool renderCube = true;
		bool key3Pressed = false;
		bool key2Pressed = false;

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			float currentFrame = (float)glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			ProcessInput(window, isPaused, spacePressed, isWireframe, key1Pressed, renderCube, key2Pressed, renderOrtoedro, key3Pressed);

			if (isWireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			if (!isPaused) {
				ortoedro.Input(window);
				
				ortoedro.Update(deltaTime);

				cube.Update(deltaTime);
				//ortoedro.Input(window);
				//pyramid.Input(window);

				for (short i = 0; i < primitives.size(); i++)
				{
					primitives[i]->Update(deltaTime);
				}
			}

			//Genero matriz de vista
			glm::mat4 viewMatrix = camera.GetViewMatrix();

			/*iDEALMENTE usar iframeWidth y height para reescalar*/
			glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			if (renderOrtoedro) {
				ortoedro.Render(viewMatrix, projectionMatrix);
				
			}
			for (short i = 0; i < primitives.size(); i++)
			{
				primitives[i]->Render(viewMatrix, projectionMatrix);
			}

			if (renderCube)
			{
				cube.Render(viewMatrix, projectionMatrix);
			}

			//Cambiamos buffers
			glfwSwapBuffers(window);
		}

		for (short i = 0; i < primitives.size(); i++)
		{
			delete primitives[i];
		}
		primitives.clear();

	}else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}
	
	//Finalizamos GLFW
	glfwTerminate();
}




