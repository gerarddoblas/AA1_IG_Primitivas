#include "Pyramid.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
Pyramid::Pyramid()
{
	Init();
}

void Pyramid::Init()
{
	//Se añade el shader
	shader.vertexShader = LoadVertexShader("MyFirstVertexShader.glsl");
	shader.fragmentShader = LoadFragmentShader("MyFirstFragmentShader.glsl");
	shaderProgram = CreateProgram(shader);

	float vertices[] =
	{
		//Cara de delante
			//Vertice de la izquierda
			-0.5f, -0.5f, 0.5f,
			//Vertice de arriba
			0.0f, 0.5f, 0.0f,
			//Vertice de la derecha
			0.5f, -0.5f, 0.5f,
			
		//Cara de la izquierda
			//Vertice de la izquierda
			-0.5f, -0.5f, 0.5f,
			//Vertice de arriba
			0.0f, 0.5f, 0.0f,
			//Vertice de la derecha
			-0.5f, -0.5f, -0.5f,

		//Cara de la derecha
			//Vertice de la izquierda
			0.5f, -0.5f, -0.5f,
			//Vertice de arriba
			0.0f, 0.5f, 0.0f,
			//Vertice de la derecha
			0.5f, -0.5f, 0.5f,

		//Cara de atras
			//Vertice de la izquierda
			0.5f, -0.5f, -0.5f,
			//Vertice de arriba
			0.0f, 0.5f, 0.0f,
			//Vertice de la derecha
			-0.5f, -0.5f, -0.5f,

		//Cara de abajo
			//Triangulo de la izquierda
				//Vertice de arriba
				-0.5f, -0.5f, 0.5f,
				//Vertice de la izquierda
				-0.5f, -0.5f, -0.5f,
				//Vertice de la derecha
				0.5f, -0.5f, -0.5f,
			//Triangulo de la derecha
				//Vertice de arriba
				0.5f, -0.5f, 0.5f,
				//Vertice de la izquierda
				-0.5f, -0.5f, 0.5f,
				//Vertice de la derecha
				0.5f, -0.5f, -0.5f,
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

void Pyramid::Update(float dt)
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

void Pyramid::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(shaderProgram);

	//Genero matrices de transformacion (model)
	glm::mat4 translationMatrix = GenerateTranslationMatrix(position);

	//Rotamos
	glm::mat4 rotationMatrixX = GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), rotation.x);
	glm::mat4 rotationMatrixY = GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), rotation.y);
	glm::mat4 rotationMatrixZ = GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), rotation.z);

	glm::mat4 rotationMatrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;
	glm::mat4 scaleMatrix = GenerateScaleMatrix(scale);

	//Pasamos las variables del shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//Definimos modo de dibujo para cada cara (solid)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Desactivar el culling para que se vea toda la piramide
	glDisable(GL_CULL_FACE);

	//Definimos que queremos usar el VAO con los puntos
	glBindVertexArray(VAO);

	//Definimos que queremos dibujar
	glDrawArrays(GL_TRIANGLES, 0, 18);

	//Dejamos de usar el VAO indicado anteriormente
	glBindVertexArray(0);
	glUseProgram(0);
}

void Pyramid::Input(GLFWwindow* window)
{

}
