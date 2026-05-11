#include "Ortoedro.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Ortoedro::Ortoedro()
{
	Init();
}

void Ortoedro::Init()
{
	shader.vertexShader   = meshRenderer->LoadVertexShader("MyFirstVertexShader.glsl");
	shader.geometryShader = meshRenderer->LoadGeometryShader("MyFirstGeometryShader.glsl");
	shader.fragmentShader = meshRenderer->LoadFragmentShader("MyFirstFragmentShader.glsl");
	shaderProgram         = meshRenderer->CreateProgram(shader);

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

	// Inicializamos el MeshRenderer 
	meshRenderer->Init(vertices, sizeof(vertices));

	//Transform
	transform->position = glm::vec3(0.0f, 0.0f, 0.0f);
	transform->rotation = glm::vec3(0.0f, 45.0f, 0.0f);
	transform->scale    = glm::vec3(ortoedroScale);
	speed               = ortoedroSpeed;
}

void Ortoedro::Update(float dt)
{
	// Rotamos 
	transform->rotation.z += rotationSpeed * speed * dt;
	if (transform->rotation.z > circle) transform->rotation.z -= circle;

	// Sumamos tiempo para la inteerpolacion
	timeAccumulator += dt;

	float cubeScaledForAnim = ortoedroWidth / ortoedroHeight;
	float maxScaleY = ortoedroScale;
	float minScaleY = ortoedroScale * cubeScaledForAnim;

	float wave = (sin(timeAccumulator * animSpeed * speed) + waveOffset) / waveScale;

	// Interpolo escala.y
	transform->scale.y = minScaleY + (maxScaleY - minScaleY) * wave;
}

void Ortoedro::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	//Indicar a la tarjeta GPU que programa debe usar
	glUseProgram(shaderProgram);

	//Genero matrices de transformacion (model)
	glm::mat4 translationMatrix = transform->GenerateTranslationMatrix(transform->position);

	//Rotamos
	glm::mat4 rotationMatrixX = transform->GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), transform->rotation.x);
	glm::mat4 rotationMatrixY = transform->GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), transform->rotation.y);
	glm::mat4 rotationMatrixZ = transform->GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), transform->rotation.z);
	glm::mat4 rotationMatrix  = rotationMatrixX * rotationMatrixY * rotationMatrixZ;

	glm::mat4 scaleMatrix = transform->GenerateScaleMatrix(transform->scale);

	//Pasamos las variables del shader
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "translationMatrix"), 1, GL_FALSE, glm::value_ptr(translationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "rotationMatrix"),    1, GL_FALSE, glm::value_ptr(rotationMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"),       1, GL_FALSE, glm::value_ptr(scaleMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "viewMatrix"),        1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projectionMatrix"),  1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//Definimos que queremos dibujar
	meshRenderer->Draw(vertexCount);

	glUseProgram(0);
}