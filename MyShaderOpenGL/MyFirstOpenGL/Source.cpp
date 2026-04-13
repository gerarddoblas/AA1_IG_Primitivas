#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Ortoedro.h"
#include "Cube.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void Resize_Window(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight) {

	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

void main()
{
	srand(time(NULL));

	
	glfwInit();

	
	//Configurar la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My Engine", NULL, NULL);

	
	glfwSetFramebufferSizeCallback(window, Resize_Window);

	
	glfwMakeContextCurrent(window);

	
	glewExperimental = GL_TRUE;

	
	glEnable(GL_CULL_FACE);

	
	glCullFace(GL_BACK);

	
	glEnable(GL_DEPTH_TEST);

	
	if (glewInit() == GLEW_OK) {

		
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Ortoedro ortoedro;

		Cube cube;

		
		while (!glfwWindowShouldClose(window)) {

			
			glfwPollEvents();

			//ortoedro.Input();
			//ortoedro.Update(0.0f);

			cube.Input();
			cube.Update(0.0f);

			
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			//ortoedro.Render();

			cube.Render();

			
			glfwSwapBuffers(window);
		}

	}else {
		std::cout << "Ha petao." << std::endl;
		glfwTerminate();
	}
	
	glfwTerminate();
}




