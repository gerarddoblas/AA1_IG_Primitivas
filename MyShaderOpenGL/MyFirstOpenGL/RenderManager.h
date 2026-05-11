#pragma once


#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <unordered_map>

#define RM RenderManager::GetInstance()

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720

class RenderManager
{
public:
    static RenderManager* GetInstance()
    {
        static RenderManager instance;
        return &instance;
    }

    struct ShaderProgram
    {
        GLuint vertexShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;
    };

    void Init();
    void Release();
    void ClearScreen();
    void RenderScreen();
    void Update(float dt);
    GLFWwindow* GetWindow() const { return _window; }

    std::string Load_File(const std::string& filePath);
    GLuint LoadVertexShader(const std::string& filePath);
    GLuint LoadFragmentShader(const std::string& filePath);
    GLuint LoadGeometryShader(const std::string& filePath);
    GLuint CreateProgram(const ShaderProgram& shaders);

private:
    RenderManager() = default;
    RenderManager(RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;
    ~RenderManager();

    GLFWwindow* _window = nullptr;
    const int OPENGL_MAJOR = 4;
    const int OPENGL_MINOR = 4;
    const char* WINDOW_TITLE = "My Engine";

    void InitGLFW();
    void CreateWindow();

    static void ResizeWindow(GLFWwindow* window, int iFrameBufferWidth, int iFrameBufferHeight);

    std::unordered_map<std::string, GLuint> _cacheShaders;
};

