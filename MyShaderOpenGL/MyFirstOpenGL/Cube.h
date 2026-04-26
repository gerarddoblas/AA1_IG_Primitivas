#pragma once
#include "Primitive.h"

class Cube : public Primitive {
public:
    Cube();
    void Init();
    void Update(float dt) override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) override;

private:
    GLuint VAO, VBO, shaderProgram;
    ShaderProgram shader;
    const glm::vec3 cubePosition = glm::vec3(-1.f, 0.0f, 0.0f);
    const glm::vec3 cubeRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    const glm::vec3 cubeScale = glm::vec3(0.25f, 0.25f, 0.25f);
    const glm::vec3 cubeForward = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec2 cubeBounds = glm::vec2(1.f, -1.f);
    const glm::vec3 cubeAngle = glm::vec3(50.0f, 50.0f, 0.0f);

    const float cubeSpeed = 1.f;
    const float maxAngle = 360.0f;
    const int vertexCount = 36;
};