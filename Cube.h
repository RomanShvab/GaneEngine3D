#pragma once

#include "Shape.h"

class Cube : public Shape {
public:
    Cube();

    virtual void draw(const glm::mat4& view, const glm::mat4& projection) override;
};