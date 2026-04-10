#pragma once
#include "Primitive.h"
class Ortoedro : public Primitive
{

public:

	Ortoedro() = default;

	// Heredado vía Primitive
	void Update(float dt) override;
	void Render() override;
	void Input() override;
};

