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
#include "Camera.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
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

		Ortoedro ortoedro;

		Camera camera;

		float lastFrame = 0.0f;
		bool isPaused = false;
		bool spacePressed = false;

		//Generamos el game loop
		while (!glfwWindowShouldClose(window)) {

			float currentFrame = (float)glfwGetTime();
			float deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			//Pulleamos los eventos (botones, teclas, mouse...)
			glfwPollEvents();

			
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
				if (!spacePressed) {
					isPaused = !isPaused;
					spacePressed = true;
				}
			}
			else {
				spacePressed = false;
			}

			if (!isPaused) {
				ortoedro.Input(window);
				
				ortoedro.Update(deltaTime);
			}

			//Genero matriz de vista
			glm::mat4 viewMatrix = camera.GetViewMatrix();

			/*iDEALMENTE usar iframeWidth y height para reescalar*/
			glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			ortoedro.Render(viewMatrix, projectionMatrix);

			//Cambiamos buffers
			glfwSwapBuffers(window);
		}

	}else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}
	
	//Finalizamos GLFW
	glfwTerminate();
}




