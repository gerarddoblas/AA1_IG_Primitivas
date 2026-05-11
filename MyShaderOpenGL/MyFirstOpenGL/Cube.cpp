#include "Cube.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
Cube::Cube() {
    Init();
}

void Cube::Init() {

    shader.vertexShader   = meshRenderer->LoadVertexShader("MyFirstVertexShader.glsl");
    shader.fragmentShader = meshRenderer->LoadFragmentShader("MyFirstFragmentShader.glsl");
    shaderProgram         = meshRenderer->CreateProgram(shader);

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
    transform->scale    = glm::vec3(0.25f);
    forward             = glm::vec3(0.0f, 1.0f, 0.0f);
    speed               = cubeSpeed;
    bounds              = glm::vec2(1.f, -1.f);
    angle               = glm::vec3(50.0f, 50.0f, 0.0f);
}

void Cube::Update(float dt)
{
    //Rotation
    transform->rotation.y += angle.y * speed * dt;
    if (transform->rotation.y > maxAngle) transform->rotation.y -= maxAngle;

    //Movement
    transform->position = transform->position + forward * speed * dt;
    if (transform->position.y >= bounds.x || transform->position.y <= bounds.y)
        forward = forward * -1.f;
}

void Cube::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(transform->GenerateTranslationMatrix(transform->position)));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(transform->GenerateRotationMatrix(glm::vec3(0, 1, 0), transform->rotation.y)));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(transform->GenerateScaleMatrix(transform->scale)));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glDisable(GL_CULL_FACE);
    meshRenderer->Draw(vertexCount);
    glEnable(GL_CULL_FACE);
}