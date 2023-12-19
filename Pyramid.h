#pragma once

#include "Shape.h"

class Pyramid : public Shape {
public:
	Pyramid();
	virtual ~Pyramid();

	virtual void draw(const glm::mat4& view, const glm::mat4& projection) override;

private:
	unsigned int VAO, VBO;
	unsigned int shaderProgram;

	void initializeShaders();
	void initializeGeometry();
};