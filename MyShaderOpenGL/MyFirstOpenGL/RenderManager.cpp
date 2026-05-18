#include "RenderManager.h"
#include "InputManager.h"
#include <cassert>

RenderManager::~RenderManager()
{
	for (auto const& [path, shader] : _cacheShaders)
	{
		glDeleteShader(shader);
	}
}

void RenderManager::ResizeWindow(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight)
{
	glViewport(0, 0, iFrameBufferWidth, iFrameBufferHeight);
}

void RenderManager::InitGLFW()
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
}

void RenderManager::CreateWindow()
{
	_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!_window) throw "Error: GLFW Window creation failed";

	glfwSetFramebufferSizeCallback(_window, ResizeWindow);
	glfwMakeContextCurrent(_window);
}

void RenderManager::Init()
{
	try
	{
		InitGLFW();
		CreateWindow();

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) throw "Error: GLEW initialization failed";

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE); // Lo desactivamos para que se vean todas las caras
		//glCullFace(GL_BACK);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	}
	catch (const char* msg)
	{
		std::cerr << msg << std::endl;
		Release();
	}
}

void RenderManager::Release()
{
	if (_window)
	{
		glfwDestroyWindow(_window);
		_window = nullptr;
	}
}

void RenderManager::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RenderManager::RenderScreen()
{
	glfwSwapBuffers(_window);
}

void RenderManager::ToggleWireframe() { _isWireframe = !_isWireframe; }

void RenderManager::Update(float dt)
{
	if (_isWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

std::string RenderManager::Load_File(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) return "";
	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

GLuint RenderManager::LoadVertexShader(const std::string& filePath)
{
	if (_cacheShaders.count(filePath)) return _cacheShaders[filePath];

	std::string source = Load_File(filePath);
	if (source.empty()) return 0;

	const char* src = source.c_str();
	GLuint shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	_cacheShaders[filePath] = shader;
	return shader;
}

GLuint RenderManager::LoadFragmentShader(const std::string& filePath)
{
	if (_cacheShaders.count(filePath)) return _cacheShaders[filePath];

	std::string source = Load_File(filePath);
	if (source.empty()) return 0;

	const char* src = source.c_str();
	GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	_cacheShaders[filePath] = shader;
	return shader;
}

GLuint RenderManager::LoadGeometryShader(const std::string& filePath)
{
	if (_cacheShaders.count(filePath)) return _cacheShaders[filePath];

	std::string source = Load_File(filePath);
	if (source.empty()) return 0;

	const char* src = source.c_str();
	GLuint shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	_cacheShaders[filePath] = shader;
	return shader;
}

GLuint RenderManager::CreateProgram(const ShaderProgram& shaders)
{
	GLuint program = glCreateProgram();
	if (shaders.vertexShader) glAttachShader(program, shaders.vertexShader);
	if (shaders.geometryShader) glAttachShader(program, shaders.geometryShader);
	if (shaders.fragmentShader) glAttachShader(program, shaders.fragmentShader);
	glLinkProgram(program);
	return program;
}
