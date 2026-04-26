#include "Ortoedro.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Ortoedro::Ortoedro()
{
	Init();
}

void Ortoedro::Init()
{
	shader.vertexShader = LoadVertexShader("MyFirstVertexShader.glsl");
	shader.geometryShader = LoadGeometryShader("MyFirstGeometryShader.glsl");
	shader.fragmentShader = LoadFragmentShader("MyFirstFragmentShader.glsl");
	shaderProgram = CreateProgram(shader);

	float vertices[] = {
		// frente 
		-0.3f, -0.8f, -0.3f,  0.3f, -0.8f, -0.3f,  0.3f,  0.8f, -0.3f,
		 0.3f,  0.8f, -0.3f, -0.3f,  0.8f, -0.3f, -0.3f, -0.8f, -0.3f,

		 // atras 
		  0.3f, -0.8f,  0.3f, -0.3f, -0.8f,  0.3f, -0.3f,  0.8f,  0.3f,
		 -0.3f,  0.8f,  0.3f,  0.3f,  0.8f,  0.3f,  0.3f, -0.8f,  0.3f,

		 // abajo
		 -0.3f, -0.8f,  0.3f,  0.3f, -0.8f,  0.3f,  0.3f, -0.8f, -0.3f,
		  0.3f, -0.8f, -0.3f, -0.3f, -0.8f, -0.3f, -0.3f, -0.8f,  0.3f,

		  // arriba 
		  -0.3f,  0.8f, -0.3f,  0.3f,  0.8f, -0.3f,  0.3f,  0.8f,  0.3f,
		   0.3f,  0.8f,  0.3f, -0.3f,  0.8f,  0.3f, -0.3f,  0.8f, -0.3f,

		   // izquierda 
		   -0.3f, -0.8f,  0.3f, -0.3f, -0.8f, -0.3f, -0.3f,  0.8f, -0.3f,
		   -0.3f,  0.8f, -0.3f, -0.3f,  0.8f,  0.3f, -0.3f, -0.8f,  0.3f,

		   // derecha 
			0.3f, -0.8f, -0.3f,  0.3f, -0.8f,  0.3f,  0.3f,  0.8f,  0.3f,
			0.3f,  0.8f,  0.3f,  0.3f,  0.8f, -0.3f,  0.3f, -0.8f, -0.3f
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
	position = glm::vec3(0.5f, 0.5f, 0.f);
	rotation = glm::vec3(0.0f, 45.f, 0.f);
	scale = glm::vec3(ortoedroScale);
}

void Ortoedro::Update(float dt)
{
	// Rotamos 
	rotation.z += rotationSpeed * dt;

	if (rotation.z > 360.0f) rotation.z -= 360.0f;

	// Sumamos tiempo para la inteerpolacion
	timeAccumulator += dt;

	
	float cubeScaledForAnim = ortoedroWidth / ortoedroHeight;

	float maxScaleY = ortoedroScale;
	float minScaleY = ortoedroScale * cubeScaledForAnim;

	
	float wave = (sin(timeAccumulator * animSpeed) + waveOffset) / waveScale;

	// Interpolo escala.y
	scale.y = minScaleY + (maxScaleY - minScaleY) * wave;
}

void Ortoedro::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(shaderProgram);

	//Genero matrices de transformacion (model)
	glm::mat4 translationMatrix = GenerateTranslationMatrix(position);
	
	//Rotamos
	glm::mat4 rotationMatrix = GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), rotation.z);
	
	glm::mat4 scaleMatrix = GenerateScaleMatrix(scale);

	//Pasamos las variables del shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"), 1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//Definimos que queremos usar el VAO con los puntos
	glBindVertexArray(VAO);
	
	//Definimos que queremos dibujar
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	//Dejamos de usar el VAO indicado anteriormente
	glBindVertexArray(0);
	glUseProgram(0);
}

void Ortoedro::Input(GLFWwindow* window)
{
}
