#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Klasa reprezentująca kamerę w przestrzeni trójwymiarowej.
 */
class Camera {
public:
    /**
     * @brief Konstruktor klasy Camera.
     * @param position Pozycja kamery w przestrzeni trójwymiarowej.
     * @param up Kierunek wektora "góra" kamery.
     * @param yaw Kąt odchylenia kamery od kierunku w lewo (w stopniach).
     * @param pitch Kąt nachylenia kamery w górę i w dół (w stopniach).
     */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    /**
     * @brief Funkcja zwracająca macierz widoku kamery.
     * @return Macierz widoku kamery.
     */
    glm::mat4 getViewMatrix();

    /**
     * @brief Funkcja obsługująca ruch kamery w odpowiedzi na naciśnięcia klawiszy.
     * @param window Wskaźnik do obiektu GLFWwindow.
     * @param deltaTime Czas od ostatniej klatki.
     */
    void processKeyboard(GLFWwindow* window, float deltaTime);

    /**
     * @brief Funkcja obsługująca ruch myszy do kontrolowania kamery.
     * @param xOffset Przesunięcie myszy w osi X.
     * @param yOffset Przesunięcie myszy w osi Y.
     * @param constrainPitch Ogranicza nachylenie kamery w górę i w dół, jeśli ustawione na true.
     */
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    /**
     * @brief Funkcja obsługująca ruch myszy do kontrolowania zoomu kamery.
     * @param yOffset Przesunięcie myszy w osi Y.
     */
    void processMouseScroll(float yOffset);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    /**
     * @brief Funkcja aktualizująca wektory kierunku kamery na podstawie kątów yaw i pitch.
     */
    void updateCameraVectors();
};
