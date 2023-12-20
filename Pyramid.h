#pragma once

#include "Shape.h"

class Pyramid : public Shape {
public:
	Pyramid();

	virtual void draw(const glm::mat4& view, const glm::mat4& projection) override;
private: 
};