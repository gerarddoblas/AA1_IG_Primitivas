#include "InputManager.h"
#include <iostream>

bool InputManager::Listen()
{
    for (std::unordered_map<GLuint, KeyState>::iterator it = _keyReference.begin(); it != _keyReference.end(); it++)
    {
        if (it->second == DOWN)
            it->second = HOLD;
        if (it->second == UP)
            it->second = RELEASED;
    }

    glfwGetCursorPos(_window, &_mouseX, &_mouseY);

    glfwPollEvents();

    return glfwWindowShouldClose(_window);
}

bool InputManager::GetKey(GLuint input, KeyState inputValue) { return _keyReference[input] == inputValue; }

void InputManager::KeyBoardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //Compruebo si la 'action' de la 'key' del teclado está presionada o soltada
    if (action == GLFW_PRESS)
        IM->_keyReference[key] = DOWN;
    else if (action == GLFW_RELEASE)
        IM->_keyReference[key] = UP;
}

void InputManager::MouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
    //Compruebo si la 'action' del ratón está presionada o soltada
    if(action == GLFW_PRESS)
        IM->_keyReference[button] = DOWN;
    else if (action == GLFW_RELEASE)
        IM->_keyReference[button] = UP;
}