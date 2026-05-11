#include "Pyramid.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Pyramid::Pyramid()
{
	Init();
}

void Pyramid::Init()
{
	//Se cargan los shaders
	shader.vertexShader   = meshRenderer->LoadVertexShader("MyFirstVertexShader.glsl");
	shader.fragmentShader = meshRenderer->LoadFragmentShader("PyramidFragmentShader.glsl");
	shaderProgram         = meshRenderer->CreateProgram(shader);

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

	// Inicializamos el MeshRenderer con la geometria de la piramide
	meshRenderer->Init(vertices, sizeof(vertices));

	//Transform
	transform->position = glm::vec3(1.f, 0.0f, 0.0f);
	transform->rotation = glm::vec3(0.0f);
	transform->scale    = glm::vec3(0.25f);
	forward             = glm::vec3(0.0f, 1.0f, 0.0f);
	speed  = pyramidSpeed;
	bounds  = glm::vec2(1.f, -1.f);
	angle = glm::vec3(50.0f, 50.0f, 0.0f);
}

void Pyramid::Update(float dt)
{
	//Rotation
	transform->rotation.x += angle.x * speed * dt;
	transform->rotation.y += angle.y * speed * dt;

	if (transform->rotation.x > maxAngle) transform->rotation.x -= maxAngle;
	if (transform->rotation.y > maxAngle) transform->rotation.y -= maxAngle;

	//Movement
	transform->position = transform->position + forward * speed * dt;

	if (transform->position.y >= bounds.x || transform->position.y <= bounds.y)
		forward = forward * -1.f;

	//Color
	colorTime += dt;

	if (colorTime >= colorInterval)
	{
		colorTime -= colorInterval;
		colorIndex = (colorIndex + 1) % NUM_COLORS;
	}
}

void Pyramid::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(shaderProgram);

	//Genero matrices de transformacion (model)
	glm::mat4 translationMatrix = transform->GenerateTranslationMatrix(transform->position);

	//Rotamos
	glm::mat4 rotationMatrixX = transform->GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), transform->rotation.x);
	glm::mat4 rotationMatrixY = transform->GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), transform->rotation.y);
	glm::mat4 rotationMatrixZ = transform->GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), transform->rotation.z);

	glm::mat4 rotationMatrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;
	glm::mat4 scaleMatrix = transform->GenerateScaleMatrix(transform->scale);

	//Vector de colores
	glm::vec3 colors[NUM_COLORS] =
	{
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f)
	};

	//Pasamos las variables del shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniform3fv(glGetUniformLocation(shaderProgram, "primitiveColor"), 1, glm::value_ptr(colors[colorIndex]));

	//Desactivar el culling para que se vea toda la piramide
	glDisable(GL_CULL_FACE);

	//Definimos que queremos dibujar
	meshRenderer->Draw(vertexCount);

	//Dejamos de usar el VAO indicado anteriormente
	glBindVertexArray(0);
	glUseProgram(0);
	glEnable(GL_CULL_FACE);
}