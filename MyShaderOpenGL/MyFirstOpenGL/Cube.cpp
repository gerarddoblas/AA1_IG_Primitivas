#include "Cube.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

Cube::Cube() {
    Init();
}

void Cube::Init() {

    shader.vertexShader = LoadVertexShader("MyFirstVertexShader.glsl");
    shader.fragmentShader = LoadFragmentShader("MyFirstFragmentShader.glsl");
    shaderProgram = CreateProgram(shader);

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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    //Transform
    position = glm::vec3(0.5f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 45.f, 0.0f);
    scale = glm::vec3(0.25f, 0.25f, 0.25f);
    forward = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 0.01f;
    bounds = glm::vec2(0.8f, -0.8f);
    angle = glm::vec3(50.0f, 50.0f, 0.0f);
}

void Cube::Update(float dt)
{
    //Rotation
    rotation.x += angle.x * dt;
    rotation.y += angle.y * dt;

    if (rotation.x > 360.0f) rotation.x -= 360.0f;
    if (rotation.y > 360.0f) rotation.y -= 360.0f;

    //Movement
    position = position + forward * speed;

    if (position.y >= bounds.x || position.y <= bounds.y)
        forward = forward * -1.f;
}

void Cube::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram);

    glm::mat4 model = GenerateTranslationMatrix(position) * GenerateRotationMatrix(glm::vec3(0, 1, 0), rotation.y);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(GenerateTranslationMatrix(position)));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(GenerateRotationMatrix(glm::vec3(0, 1, 0), rotation.y)));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    glDisable(GL_CULL_FACE);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Cube::Input(GLFWwindow* window) {}
