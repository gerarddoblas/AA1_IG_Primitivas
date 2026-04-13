#pragma once
#include "Primitive.h"

class Cube : public Primitive
{
public:
    Cube() = default;

    void Update(float dt) override;
    void Render() override;
    void Input() override;

private:
    GLuint VAO, VBO;
    GLuint shaderProgram;
    ShaderProgram shader;
};