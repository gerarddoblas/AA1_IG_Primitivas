#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>

#define IM InputManager::GetInstance()

enum KeyState { EMPTY, DOWN, UP, HOLD, RELEASED };

class InputManager
{
public:
	static InputManager* GetInstance()
	{
		static InputManager instance;
		return &instance;
	}

	void Init(GLFWwindow* window)
	{
		_window = window;

		glfwSetKeyCallback(_window, KeyBoardCallBack);
		glfwSetMouseButtonCallback(_window, MouseCallBack);
	}

	bool Listen();

	double GetMouseX() const { return _mouseX; }
	double GetMouseY() const { return _mouseY; }
	bool GetKey(GLuint input, KeyState inputValue);

private:
	InputManager() = default;
	InputManager(InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	~InputManager() {}

	static void KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseCallBack(GLFWwindow* window, int button, int action, int mods);

	GLFWwindow* _window = nullptr;

	//Son double porque glfwGetCursorPos() me obliga a pasar doubles, no hago cast por perdida de datos
	double _mouseX = 0;
	double _mouseY = 0;

	std::unordered_map<GLuint, KeyState> _keyReference;
};