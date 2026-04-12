#include "Ortoedro.h"

void Ortoedro::Update(float dt)
{
}

void Ortoedro::Render()
{
	
		// Init
		shader.vertexShader = Primitive::LoadVertexShader("VertexShader.glsl");
		shader.fragmentShader = Primitive::LoadFragmentShader("MyFirstFragmentShader.glsl");
		shaderProgram = Primitive::CreateProgram(shader);

		float vertices[] = {
			// frente
			-0.3f, -0.8f, -0.3f,
			 0.3f, -0.8f, -0.3f,
			 0.3f,  0.8f, -0.3f,
			 0.3f,  0.8f, -0.3f,
			-0.3f,  0.8f, -0.3f,
			-0.3f, -0.8f, -0.3f,
			
			// atras
			-0.3f, -0.8f,  0.3f,
			 0.3f, -0.8f,  0.3f,
			 0.3f,  0.8f,  0.3f,
			 0.3f,  0.8f,  0.3f,
			-0.3f,  0.8f,  0.3f,
			-0.3f, -0.8f,  0.3f,
			
			// abajo
			-0.3f, -0.8f, -0.3f,
			 0.3f, -0.8f, -0.3f,
			 0.3f, -0.8f,  0.3f,
			 0.3f, -0.8f,  0.3f,
			-0.3f, -0.8f,  0.3f,
			-0.3f, -0.8f, -0.3f,
			
			// arriba
			 0.3f,  0.8f, -0.3f,
			-0.3f,  0.8f, -0.3f,
			-0.3f,  0.8f,  0.3f,
			-0.3f,  0.8f,  0.3f,
			 0.3f,  0.8f,  0.3f,
			 0.3f,  0.8f, -0.3f,
			
			// izquierda
			-0.3f, -0.8f, -0.3f,
			-0.3f,  0.8f, -0.3f,
			-0.3f,  0.8f,  0.3f,
			-0.3f,  0.8f,  0.3f,
			-0.3f, -0.8f,  0.3f,
			-0.3f, -0.8f, -0.3f,
			
			// derecha
			 0.3f, -0.8f, -0.3f,
			 0.3f,  0.8f, -0.3f,
			 0.3f,  0.8f,  0.3f,
			 0.3f,  0.8f,  0.3f,
			 0.3f, -0.8f,  0.3f,
			 0.3f, -0.8f, -0.3f
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
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Ortoedro::Input()
{
	
}
