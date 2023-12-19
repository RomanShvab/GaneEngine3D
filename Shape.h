#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shape {
public:
    virtual ~Shape() {}

    virtual void draw(const glm::mat4& view, const glm::mat4& projection) = 0;
};