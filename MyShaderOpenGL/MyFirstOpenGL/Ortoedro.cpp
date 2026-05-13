#include "Ortoedro.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "RenderManager.h"

Ortoedro::Ortoedro()
{
	Init();
}

void Ortoedro::Init()
{
    RenderManager::ShaderProgram shaders;
    shaders.vertexShader = RM->LoadVertexShader("MyFirstVertexShader.glsl");
    shaders.fragmentShader = RM->LoadFragmentShader("MyFirstFragmentShader.glsl");
    shaderProgram = RM->CreateProgram(shaders);

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
    transform->position = glm::vec3(0.0f);
    transform->rotation = glm::vec3(0.0f);
    transform->scale = glm::vec3(0.35f);
}

void Ortoedro::Update(float dt)
{
    // Rotamos eje Z
    transform->rotation.z += rotationSpeed * dt;
    if (transform->rotation.z >= circle) transform->rotation.z -= circle;

    // inclino para ver 3d
    transform->rotation.x = 25.0f;
    transform->rotation.y = 25.0f;

	// Sumamos tiempo para la inteerpolacion
    timeAccumulator += dt;

    // Interpolamos entre minimo del ortoedro y el maximo
	float cubeScaledForAnim = ortoedroWidth / ortoedroHeight;
	float maxScaleY = ortoedroScale;
	float minScaleY = ortoedroScale * cubeScaledForAnim;

	float wave = (sin(timeAccumulator * animSpeed) + waveOffset) / waveScale;

	// Interpolo escala.y
	transform->scale.y = minScaleY + (maxScaleY - minScaleY) * wave;
}

void Ortoedro::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    // Usar el draw para renderizar y el uniform para saber el centro de la window
    meshRenderer->Draw(shaderProgram, transform->GetTranslationMatrix(), transform->GetRotationMatrix(), transform->GetScaleMatrix(), viewMatrix, projectionMatrix, vertexCount);
    glUniform1f(glGetUniformLocation(shaderProgram, "windowHeight"), (float)WINDOW_HEIGHT);
}