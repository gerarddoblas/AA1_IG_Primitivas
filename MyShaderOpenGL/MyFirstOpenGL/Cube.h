#pragma once
#include "Primitive.h"

class Cube : public Primitive {
public:
    Cube();
    void Init();
    void Update(float dt) override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;
    void Input(GLFWwindow* window) override;

private:
    GLuint VAO, VBO, shaderProgram;
    ShaderProgram shader;
    glm::vec3 position = glm::vec3(-0.5f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
};