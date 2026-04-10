#pragma once
#include "Primitive.h"

class Cube : public Primitive
{
public:
    Cube();

    void Update(float dt) override;
    void Render() override;
    void Input() override;
};