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

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

const float SPEED_MULTIPLIER_UP = 1.1f;
const float SPEED_MULTIPLIER_DOWN = 0.9f;
const int OPENGL_MAJOR = 4;
const int OPENGL_MINOR = 4;
const char* WINDOW_TITLE = "My Engine";

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	//Definir nuevo tamaño del viewport
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

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

	
	//Configurar la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//Inicializamos la ventana
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	//Asignamos función de callback para cuando el frame buffer es modificado
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	//Definimos espacio de trabajo
	glfwMakeContextCurrent(window);

	//Inizializo el Inputmanager
	IM->Init(window);

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

			if (!IM->GetKey(GLFW_KEY_SPACE, HOLD))
			{
				for (std::unordered_map<PrimitiveType, Primitive*>::iterator it = primitives.begin(); it != primitives.end(); it++)
					it->second->Update(deltaTime);
			}

			if (IM->GetKey(GLFW_KEY_1, HOLD))
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//Genero matriz de vista
			glm::mat4 viewMatrix = camera.GetViewMatrix();
			glm::mat4 projectionMatrix = camera.GetProjectionMatrix((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

			//Limpiamos los buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			for (std::unordered_map<PrimitiveType, Primitive*>::iterator it = primitives.begin(); it != primitives.end(); it++)
			{
				if(it->second->isVisible)
					it->second->Render(viewMatrix, projectionMatrix);
			}
			glfwSwapBuffers(window);
		}

		for (std::unordered_map<PrimitiveType, Primitive*>::iterator it = primitives.begin(); it != primitives.end(); it++)
			delete it->second;

		primitives.clear();

	}else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}
	glfwTerminate();
}