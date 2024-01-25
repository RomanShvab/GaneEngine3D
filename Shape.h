#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Klasa reprezentująca abstrakcyjny kształt.
 */
class Shape {
public:
    /**
     * @brief Konstruktor domyślny dla klasy Shape.
     */
    Shape();

    /**
     * @brief Destruktor dla klasy Shape.
     */
    ~Shape();

    /**
     * @brief Ustawia pozycję kształtu w przestrzeni trójwymiarowej.
     * @param x Współrzędna X.
     * @param y Współrzędna Y.
     * @param z Współrzędna Z.
     */
    void setPosition(float x, float y, float z);

    /**
     * @brief Obraca kształt wokół danej osi o zadany kąt.
     * @param x Składowa X wektora obrotu.
     * @param y Składowa Y wektora obrotu.
     * @param z Składowa Z wektora obrotu.
     * @param angle Kąt obrotu w stopniach.
     */
    void rotateAtAngle(float x, float y, float z, float angle);

    /**
     * @brief Obraca kształt wokół danej osi z zadaną prędkością.
     * @param x Składowa X wektora obrotu.
     * @param y Składowa Y wektora obrotu.
     * @param z Składowa Z wektora obrotu.
     * @param speed Prędkość obrotu (domyślnie 1).
     */
    void rotate(float x, float y, float z, float speed = 1);

    /**
     * @brief Przesuwa kształt o zadaną wartość wzdłuż osi X, Y, Z.
     * @param x Wartość przesunięcia wzdłuż osi X.
     * @param y Wartość przesunięcia wzdłuż osi Y.
     * @param z Wartość przesunięcia wzdłuż osi Z.
     * @param deltaTime Czas od ostatniej klatki.
     */
    void move(float x, float y, float z, float deltaTime);

    /**
     * @brief Ustawia kolor kształtu.
     * @param R Składowa czerwona (0.0 - 1.0).
     * @param G Składowa zielona (0.0 - 1.0).
     * @param B Składowa niebieska (0.0 - 1.0).
     * @param A Składowa alpha (przezroczystość, 0.0 - 1.0).
     */
    void setColor(float R, float G, float B, float A);

    /**
     * @brief Czysto wirtualna funkcja rysująca kształt.
     * @param view Macierz widoku.
     * @param projection Macierz projekcji.
     */
    virtual void draw(const glm::mat4& view, const glm::mat4& projection) = 0;

protected:
    glm::vec3 position;     ///< Aktualna pozycja kształtu.
    glm::vec4 color;        ///< Aktualny kolor kształtu (RGBA).
    glm::mat4 model;        ///< Macierz modelu do transformacji obiektu.
    double lastFrame;       ///< Czas ostatniej klatki.
    unsigned int VAO, VBO;  ///< Identyfikatory buforów dla OpenGL.
    unsigned int shaderProgram; ///< Identyfikator programu cieniowania.

    /**
     * @brief Inicjalizuje shadery dla kształtu.
     */
    void initializeShaders();

    /**
     * @brief Inicjalizuje bufory VAO i VBO dla kształtu.
     * @param vertices Wskaźnik do tablicy zawierającej wierzchołki kształtu.
     * @param size Rozmiar tablicy wierzchołków.
     */
    void initializeVAOVBO(float* vertices, size_t size);
};
