#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Pyramid.h"
#include "Cube.h"
#include "Camera.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // Inicjalizacja GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    // Konfiguracja GLFW
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Utworzenie okna GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Rotating Shapes", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicjalizacja GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Konfiguracja widoku i callbacków
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Ustawienia kamery
    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // Klasa dla piramidy
    Pyramid pyramid;
    pyramid.setPosition(-1, -1, -1);
    pyramid.setColor(1.0f, 0.0f, 0.0f, 1.0f);

    // Klasa dla kostki
    Cube cube;
    cube.setColor(0.0f, 1.0f, 0.0f, 1.0f);

    double lastFrameTime = glfwGetTime();
    double lastMouseX, lastMouseY;
    bool firstMouse = true;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    while (!glfwWindowShouldClose(window)) {

        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastFrameTime);
        lastFrameTime = currentTime;
        // Obsługa wejść
        processInput(window);
        float time = glfwGetTime();

        // Ruch myszy
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        if (firstMouse) {
            lastMouseX = mouseX;
            lastMouseY = mouseY;
            firstMouse = false;
        }

        double xOffset = mouseX - lastMouseX;
        double yOffset = lastMouseY - mouseY;

        lastMouseX = mouseX;
        lastMouseY = mouseY;

        camera.processMouseMovement(static_cast<float>(xOffset), static_cast<float>(yOffset));

        // Rysowanie
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 view = camera.getViewMatrix();
        camera.processKeyboard(window, deltaTime);

        // Rysowanie piramidy
        pyramid.move(1, 0, 0, deltaTime);
        pyramid.rotate(0.0f, 1.0f, 0.0f);
        pyramid.draw(view, projection);

        // Rysowanie kostki
        cube.setPosition(1, 1, 1);
        cube.rotate(1.0f, 0.0f, 0.0f);
        cube.draw(view, projection);

        // Zamiana buforów i obsługa zdarzeń
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Zamknięcie okna
    glfwTerminate();

    return 0;
}