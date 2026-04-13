#pragma once
#include "Primitive.h"
class Ortoedro : public Primitive
{

public:

	Ortoedro() = default;

	
	void Update(float dt) override;
	void Render() override;
	void Input() override;

private:
	GLuint VAO, VBO;
	GLuint shaderProgram;
	ShaderProgram shader;
};

