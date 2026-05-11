#include "RenderManager.h"
#include <cassert>

#include <iostream>

RenderManager::~RenderManager()
{
	for (std::unordered_map<std::string, GLuint>::iterator it = _cacheShaders.begin(); it != _cacheShaders.end(); it++)
	{
		//Se elimina cada Shader
		glDeleteShader(it->second);
	}
}

void RenderManager::ResizeWindow(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight)
{
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

void RenderManager::InitGLFW()
{
	//Configurar la ventana
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

void RenderManager::CreateWindow()
{
		//Inicializamos la ventana
		_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
		
		if (!_window)
			throw "Ha habido un error al inicializar la ventana";

		//Asignamos función de callback para cuando el frame buffer es modificado
		glfwSetFramebufferSizeCallback(_window, ResizeWindow);

		//Definimos espacio de trabajo
		glfwMakeContextCurrent(_window);
}

void RenderManager::Init()
{
	try
	{
		//Se inicializa la ventana
		InitGLFW();

		//Se crea la ventana
		CreateWindow();

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

		}
		else
			throw "El glewInit fallo";
	}
	catch (...)
	{
		Release();
		return;
	}
}

void RenderManager::Release()
{
	//Se destruye la Ventana
	glfwDestroyWindow(_window);
	_window = nullptr;
}

void RenderManager::ClearScreen()
{
	//Limpiamos los tres buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderManager::RenderScreen()
{
	//Cambia un buffer por otro
	glfwSwapBuffers(_window);
}

void RenderManager::Update(float dt)
{
	////Cambiar al Update del RM
	//if (IM->GetKey(GLFW_KEY_1, HOLD))
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//else
	//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}