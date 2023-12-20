#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shape {
public:
    Shape();
    ~Shape();

    void setPosition(float x, float y, float z);
    void rotateAtAngle(float x, float y, float z, float angle);
    void rotate(float x, float y, float z, float speed = 1); 
    void move(float x, float y, float z, float deltaTime);
    void setColor(float R, float G, float B, float A);

    virtual void draw(const glm::mat4& view, const glm::mat4& projection) = 0;
protected:
    glm::vec3 position;
    glm::vec4 color;
    glm::mat4 model;
    double lastFrame;
    unsigned int VAO, VBO;
    unsigned int shaderProgram;
    void initializeShaders();
    void initializeVAOVBO(float* vertices, size_t size);
};