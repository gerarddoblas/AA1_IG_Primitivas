#include "Cube.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include "RenderManager.h"
Cube::Cube() {
    Init();
}

void Cube::Init() {
    RenderManager::ShaderProgram shaders;
    shaders.vertexShader = RM->LoadVertexShader("MyFirstVertexShader.glsl");
    shaders.fragmentShader = RM->LoadFragmentShader("MyFirstFragmentShader.glsl");
    shaderProgram = RM->CreateProgram(shaders);

    float vertices[] = {
        // Cara trasera
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
        // Cara frontal
        -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,
        // Cara izquierda
        -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
        // Cara derecha
         0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
         // Cara inferior
        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,
         // Cara superior
        -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f
    };

    // Inicializamos el MeshRenderer
    meshRenderer->Init(vertices, sizeof(vertices));

    //Transform
    transform->position = glm::vec3(-1.f, 0.0f, 0.0f);
    transform->rotation = glm::vec3(0.0f);
    transform->scale = glm::vec3(0.25f);
    forward = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = cubeSpeed;
    bounds = glm::vec2(1.f, -1.f);
    angle = glm::vec3(50.0f, 50.0f, 0.0f);
}

void Cube::Update(float dt)
{
    //Rotation
    transform->rotation.y += angle.y * speed * dt;
    if (transform->rotation.y > maxAngle) transform->rotation.y -= maxAngle;

    //Movement
    transform->position += forward * speed * dt;
    if (transform->position.y >= bounds.x || transform->position.y <= bounds.y)
        forward *= -1.f;
}

void Cube::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    meshRenderer->Draw(shaderProgram, transform->GetTranslationMatrix(), transform->GetRotationMatrix(), transform->GetScaleMatrix(), viewMatrix, projectionMatrix, vertexCount);
    glUniform1f(glGetUniformLocation(shaderProgram, "windowHeight"), (float)WINDOW_HEIGHT);
}