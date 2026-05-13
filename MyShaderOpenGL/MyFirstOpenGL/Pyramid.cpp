#include "Pyramid.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "RenderManager.h"

Pyramid::Pyramid()
{
	Init();
}

void Pyramid::Init()
{
	// Se cargan los shaders a través del RenderManager
    RenderManager::ShaderProgram shaders;
    shaders.vertexShader   = RM->LoadVertexShader("MyFirstVertexShader.glsl");
    shaders.fragmentShader = RM->LoadFragmentShader("PyramidFragmentShader.glsl");
    shaderProgram          = RM->CreateProgram(shaders);

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
    transform->scale = glm::vec3(0.25f);
    forward = glm::vec3(0.0f, 1.0f, 0.0f);
	speed = pyramidSpeed;
	bounds = glm::vec2(1.f, -1.f);
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
        forward *= -1.f;

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
	//Vector de colores
	glm::vec3 colors[NUM_COLORS] =
	{
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    };

    // Draw pasamos el mvp
    meshRenderer->Draw(shaderProgram, transform->GetTranslationMatrix(), transform->GetRotationMatrix(), transform->GetScaleMatrix(), viewMatrix, projectionMatrix, vertexCount);

    // Despues enviamos el uniforme extra especifico de la piramide
    glUniform3fv(glGetUniformLocation(shaderProgram, "primitiveColor"), 1, glm::value_ptr(colors[colorIndex]));
}