#include "Camera.h"

/**
 * @brief Konstruktor klasy Camera.
 * Inicjalizuje kamerę ustawiając jej początkową pozycję, kierunek wektorów "góra", kąty yaw i pitch oraz parametry ruchu i czułości myszy.
 * @param position Pozycja kamery w przestrzeni trójwymiarowej.
 * @param up Kierunek wektora "góra" kamery.
 * @param yaw Kąt odchylenia kamery od kierunku w lewo (w stopniach).
 * @param pitch Kąt nachylenia kamery w górę i w dół (w stopniach).
 */
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    movementSpeed(2.5f),
    mouseSensitivity(0.1f),
    zoom(45.0f)
{
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

/**
 * @brief Funkcja zwracająca macierz widoku kamery.
 * @return Macierz widoku kamery.
 */
glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

/**
 * @brief Funkcja obsługująca ruch kamery w odpowiedzi na naciśnięcia klawiszy.
 * @param window Wskaźnik do obiektu GLFWwindow.
 * @param deltaTime Czas od ostatniej klatki.
 */
void Camera::processKeyboard(GLFWwindow* window, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * velocity;
}

/**
 * @brief Funkcja obsługująca ruch myszy do kontrolowania kamery.
 * @param xOffset Przesunięcie myszy w osi X.
 * @param yOffset Przesunięcie myszy w osi Y.
 * @param constrainPitch Ogranicza nachylenie kamery w górę i w dół, jeśli ustawione na true.
 */
void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    updateCameraVectors();
}

/**
 * @brief Funkcja obsługująca ruch myszy do kontrolowania zoomu kamery.
 * @param yOffset Przesunięcie myszy w osi Y.
 */
void Camera::processMouseScroll(float yOffset) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yOffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

/**
 * @brief Funkcja aktualizująca wektory kierunku kamery na podstawie kątów yaw i pitch.
 */
void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
