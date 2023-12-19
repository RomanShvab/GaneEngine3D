#pragma once

#include "Shape.h"

class Cube : public Shape {
public:
    Cube();

    virtual ~Cube();

    virtual void draw(const glm::mat4& view, const glm::mat4& projection) override;
    void SetPosition(const glm::vec3& newPosition);

private:
    unsigned int VAO, VBO;
    unsigned int shaderProgram;
    glm::vec3 position;

    void initializeShaders();

    void initializeGeometry();
};