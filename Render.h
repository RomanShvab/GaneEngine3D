#pragma once

#include "Shader.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Renderer {
public:
    Renderer();
    ~Renderer();

    void run();

private:
    Shader shader;
    GLFWwindow* window;
    unsigned int VAO, VBO, normalVBO;

    void initialize();
    void render();
    void processInput(GLFWwindow* window);
};