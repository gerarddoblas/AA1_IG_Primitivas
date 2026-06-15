#pragma once
#include "Scene.h"
#include "Cube.h"
#include "Ortoedro.h"
#include "Pyramid.h"

class MainScene : public Scene {
public:
    void OnEnter() override {
        // Inicializamos los objetos en la entrada de la escena
        AddGameObject(new Cube());
        AddGameObject(new Ortoedro());
        AddGameObject(new Pyramid());
    }
};
