============================================================
PROYECTO: PRIMITIVAS OPENGL - MOTOR DE VIDEOJUEGOS
============================================================

CÓDIGO FUENTE REFACTORIZADO/GENERADO POR IA

--- Scene.h ---
#pragma once
#include <vector>
#include <glm.hpp>
#include "GameObject.h"
PREGUNTA: ESTE CODIGO DE SCENE ME DA ERROR A VECES  EN EL EN EL GAMEOBJECT que no se ven

class Scene {
protected:
	std::vector<GameObject*> objects;
	std::vector<GameObject*> ui;

public:
	Scene() = default;
	virtual ~Scene() { OnExit(); }
	virtual void OnEnter() = 0;
	virtual void OnExit() {
		for (GameObject* o : objects) delete o;
		objects.clear();
	}
	virtual void Update(float dt) {
		for (int i = objects.size() - 1; i >= 0; i--) {
			if (objects[i]->isPendingDestroy) {
				delete objects[i];
				objects.erase(objects.begin() + i);
			}
		}
		for (GameObject* o : objects) o->Update(dt);
	}
	virtual void Render(const glm::mat4& v, const glm::mat4& p) {
		for (GameObject* o : objects) o->Render(v, p);
	}
	void AddGameObject(GameObject* obj) {objects.push_back(obj); }
	std::vector<GameObject*>& GetObjects() { return objects; }
};


RESPUESTA: 
class Scene {
protected:
	std::vector<GameObject*> objects;
	std::vector<GameObject*> ui;

public:
	Scene() = default;
	virtual ~Scene() { OnExit(); }
	virtual void OnEnter() = 0;
	virtual void OnExit() {
		for (GameObject* o : objects) delete o;
		objects.clear();
	}
	virtual void Update(float dt) {
		for (int i = objects.size() - 1; i >= 0; i--) {
			if (objects[i]->isPendingDestroy) {
				delete objects[i];
				objects.erase(objects.begin() + i);
			}
		}
		for (GameObject* o : objects) if (o && o->isVisible) o->Update(dt);
	}
	virtual void Render(const glm::mat4& v, const glm::mat4& p) {
		for (GameObject* o : objects) if (o && o->isVisible) o->Render(v, p);
	}
	void AddGameObject(GameObject* obj) {if(obj) objects.push_back(obj); }
	std::vector<GameObject*>& GetObjects() { return objects; }
};

PREGUNTA: No entiendo porque al intentar generar la rotacion me da error tengo que pasarlo a radians? que asumo que tendre que hacer lo mismo para el scale y el modelo se que hay que multiplicar los 3 pero los generate o los get?

glm::mat4 Transform::GenerateScaleMatrix(glm::vec3 s) const { return glm::scale(glm::mat4(1.f), s); }
glm::mat4 Transform::GenerateRotationMatrix(glm::vec3 a, float d) const { return glm::rotate(glm::mat4(1.f), glm::radians(d), a); }
glm::mat4 Transform::GenerateTranslationMatrix(glm::vec3 t) const { return glm::translate(glm::mat4(1.f), t); }
glm::mat4 Transform::GetTranslationMatrix() const { return GenerateTranslationMatrix(position); }
glm::mat4 Transform::GetRotationMatrix() const {
	glm::vec3 r; 
	r.x = rotation.x;
	r.y = rotation.y;
	r.z = rotation.z;
	return r;
}


RESPUESTA

glm::mat4 Transform::GetRotationMatrix() const {
	glm::mat4 r = GenerateRotationMatrix(glm::vec3(1,0,0), rotation.x);
	r = glm::rotate(r, glm::radians(rotation.y), glm::vec3(0,1,0));
	r = glm::rotate(r, glm::radians(rotation.z), glm::vec3(0,0,1));
	return r;
}
glm::mat4 Transform::GetScaleMatrix() const { return GenerateScaleMatrix(scale); }
glm::mat4 Transform::GetModelMatrix() const { return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix(); }



PREGUNTA, EN EL MESH RENDERER TENGO EL DRAW PERO QUE FALTA?
class MeshRenderer
{
public:
	
	void Init(float* vertices, int byteSize);

	
	void Draw(const glm::mat4& translation, const glm::mat4& rotation, const glm::mat4& scale, const glm::mat4& view, const glm::mat4& projection);

private:
	GLuint vao = 0;
	GLuint vbo = 0;
};


RESPUESTA:
class MeshRenderer
{
public:
	// Inicializamos con los vertices
	void Init(float* vertices, int byteSize);

	// Dibujamos usando un programa de shader y las matrices de transformacion
	void Draw(GLuint shaderProgram, const glm::mat4& translation, const glm::mat4& rotation, const glm::mat4& scale, const glm::mat4& view, const glm::mat4& projection, int vertexCount);

private:
	GLuint vao = 0;
	GLuint vbo = 0;
};


PREGUNTA: 
¿Solo  puedo hacer que el ortoedro esté continuamente escalando sus dimensiones como consigo que tambien este desescalando sus dimensiones para convertirse en un cubo y después vuelva a su tamaño original?"*

RESPUESTA Hemos integrado un `timeAccumulator` que registra el tiempo transcurrido entre frames. Mediante una función `sin()`, creamos una oscilación que permite interpolar el tamaño en el eje Y de forma cíclica.
cpp
void Ortoedro::Update(float dt) {
    rotation.z += 50.0f * dt;
    if (rotation.z > 360.0f) rotation.z -= 360.0f;
    timeAccumulator += dt;
    float cubeScaledForAnim = ortoedroWidth / ortoedroHeight;
    float minScaleY = ortoedroScale * cubeScaledForAnim;
    float wave = (sin(timeAccumulator * animSpeed) + waveOffset) / waveScale;
    scale.y = minScaleY + (ortoedroScale - minScaleY) * wave;
}


PREGUNTA: LAS TECLAS FUNCIONAN PERO TENGO UN NUMERO TAL CUAL Y VA RARO CON EL TIEMPO 

RESPUESTA: 
while (!IM->Listen()) {
    TIME.Update();
    if (!_isPaused) {
        if (IM->GetKey(GLFW_KEY_M, DOWN)) TIME.SetTimeMultiplier(TIME.GetTimeMultiplier() * 1.1f); <-- Añadidas estos dos GetTime
        if (IM->GetKey(GLFW_KEY_N, DOWN)) TIME.SetTimeMultiplier(TIME.GetTimeMultiplier() * 0.9f);
        if (IM->GetKey(GLFW_KEY_1, DOWN)) RM->ToggleWireframe();
        SM.UpdateCurrentScene(TIME.GetDeltaTime());
    }
    RM->ClearScreen();
    if (SM.GetCurrentScene()) SM.GetCurrentScene()->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(aspect));
    RM->RenderScreen();
}

PREGUNTA
"Hemos juntado el trabajo de todos y se veía bien hasta que hemos agregado el cube y creo que algo falla porque hasta la vista de la cámara cambió."*


RESPUESTA
Descubrí que al renderizar el Cubo se estaba desactivando el *culling* (`glDisable(GL_CULL_FACE)`) pero nunca se volvía a activar. Al funcionar OpenGL como una máquina de estados, esto rompía el renderizado de las primitivas que iban después haciendo que se vieran "del revés".
Además, el Cubo no se estaba moviendo porque faltaba llamar a su `Update` en el bucle del juego, y la tecla '2' para ocultarlo fallaba porque se le olvidó poner una referencia `&` en `ProcessInput`.


**Código modificado:**
En `Source.cpp`, arreglamos los inputs y añadimos el Update:
```cpp
// Antes
void ProcessInput(..., bool key2Pressed, ...)
// Después
void ProcessInput(..., bool& key2Pressed, ...)


// En el bucle principal de Source.cpp:
if (!isPaused) {
    for (short i = 0; i < primitives.size(); i++) {
        primitives[i]->Update(deltaTime);
    }
    cube.Update(deltaTime); // <-- Línea añadida
}


PREGUNTA:
"El cubo es enorme y los otros no y antes la pirámide iba de arriba a abajo de la pantalla y ahora no, empieza por hacer las 3 figuras ponerlas en pos.y centrada en la izquierda el cubo, centro ortoedro y derecha pyramid"*


RESPUESTA
El cubo ignoraba su escala porque en su `Render()` pasaba una matriz identidad en lugar de su propia matriz. Luego modifiqué los métodos `Init()` para alinear todos en `y = 0` y esparcidos en `X`.
Finalmente, la pirámide apenas se veía rebotar porque la Cámara estaba en una esquina superior (`2, 2, 3`) mirando en diagonal; la centré `(0, 0, 3)` mirando al frente y el rebote volvió a apreciarse correctamente.


**Código modificado:**
Alineación en los métodos `Init()` de cada clase:
```cpp
// Cube::Init() (Izquierda)
position = glm::vec3(-0.8f, 0.0f, 0.0f);


// Ortoedro::Init() (Centro)
position = glm::vec3(0.0f, 0.0f, 0.0f);


// Pyramid::Init() (Derecha)
position = glm::vec3(0.8f, 0.0f, 0.0f);
```


Escala del cubo corregida en `Cube::Render()`:
```cpp
// Antes
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));


// Después
glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "scaleMatrix"), 1, GL_FALSE, glm::value_ptr(GenerateScaleMatrix(scale)));


PREGUNTA: 
No lo veo 3d el ortoedro


RESPUESTA
Sin `glEnable(GL_DEPTH_TEST)`, OpenGL dibuja los polígonos unos encima de otros en el orden en el que están en el código en lugar de su profundidad real en 3D (las caras de atrás tapaban a las de delante). Además arreglé el `glCullFace` que estaba configurado en `GL_FRONT` para que fuese `GL_BACK` (el estándar).


**Código modificado:**
Añadido a la función `main()` de `Source.cpp`:
```cpp
// Antes
glEnable(GL_CULL_FACE);
glCullFace(GL_FRONT);


// Después
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);         // <-- Corregido para culling normal
glEnable(GL_DEPTH_TEST);     // <-- Añadido para habilitar la profundidad 3D


PREGUNTA:

Es que ha de rotar en z  y rota en y

RESPUESTA:

El problema real era que en `Init()` el Ortoedro tenía una inclinación inicial de 45 grados en Y (`rotation.y = 45.f`) para que se viera 3D, pero en el `Render()` esa inclinación se ignoraba totalmente.
Modifiqué el `Render()` del Ortoedro para que combine (multiplique) las matrices de X, Y y Z. Así conserva la inclinación inicial pero continúa rotando en el eje Z como querías.


**Código modificado:**
En `Ortoedro::Render()`:
```cpp
// Antes
glm::mat4 rotationMatrix = GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), rotation.z);


// Después
glm::mat4 rotationMatrixX = GenerateRotationMatrix(glm::vec3(1.f, 0.f, 0.f), rotation.x);
glm::mat4 rotationMatrixY = GenerateRotationMatrix(glm::vec3(0.f, 1.f, 0.f), rotation.y);
glm::mat4 rotationMatrixZ = GenerateRotationMatrix(glm::vec3(0.f, 0.f, 1.f), rotation.z);
glm::mat4 rotationMatrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;


PREGUNTA:

¿Está bien el meshRenderer, es un buen game engine? ¿Qué mejorarías?


RESPUESTA: 
Se determinó que es un **excelente punto de partida con fines educativos**. Cumple su función básica (usando VAOs y VBOs). Sin embargo, bajo estándares de motores profesionales, se recomendaron las siguientes mejoras. A continuación se muestra cómo se implementarían en código:


Limpieza de Memoria (Destructor)
Actualmente, los buffers de la tarjeta gráfica no se borran cuando el programa termina o se destruye el objeto, lo que causa un "memory leak" (fuga de memoria VRAM).


Solución en código:
```cpp
// En MeshRenderer.h
public:
    ~MeshRenderer();


// En MeshRenderer.cpp
MeshRenderer::~MeshRenderer() {
    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
    }
    if (vbo != 0) {
        glDeleteBuffers(1, &vbo);
    }
}



