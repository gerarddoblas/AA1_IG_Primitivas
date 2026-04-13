#include "Cube.h"

void Cube::Update(float dt)
{
    
}

void Cube::Render()
{
    // Init
    shader.vertexShader = Primitive::LoadVertexShader("MyFirstVertexShader.glsl");
    shader.fragmentShader = Primitive::LoadFragmentShader("MyFirstFragmentShader.glsl");
    shaderProgram = Primitive::CreateProgram(shader);

    float vertices[] = {

            -0.5f, +0.5f, -0.5f, // 3
            +0.5f, +0.5f, -0.5f, // 2
            -0.5f, -0.5f, -0.5f, // 6
            +0.5f, -0.5f, -0.5f, // 7
            +0.5f, -0.5f, +0.5f, // 4
            +0.5f, +0.5f, -0.5f, // 2
            +0.5f, +0.5f, +0.5f, // 0
            -0.5f, +0.5f, -0.5f, // 3
            -0.5f, +0.5f, +0.5f, // 1
            -0.5f, -0.5f, -0.5f, // 6
            -0.5f, -0.5f, +0.5f, // 5
            +0.5f, -0.5f, +0.5f, // 4
            -0.5f, +0.5f, +0.5f, // 1
            +0.5f, +0.5f, +0.5f  // 0
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);



    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 14);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Cube::Input()
{
}
