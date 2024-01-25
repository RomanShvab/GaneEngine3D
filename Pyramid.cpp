﻿#include "Pyramid.h"

/**
 * @brief Konstruktor dla klasy Pyramid.
 * Inicjalizuje piramidę poprzez przekazanie odpowiednich wierzchołków do funkcji initializeVAOVBO.
 */
Pyramid::Pyramid()
{
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.0f,  0.5f,  0.0f,

         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.0f,  0.5f,  0.0f,

         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
         0.0f,  0.5f,  0.0f,

        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.0f,  0.5f,  0.0f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,

         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f
    };
    initializeVAOVBO(vertices, sizeof(vertices));
}

/**
 * @brief Funkcja rysująca piramidę.
 * Ustawia parametry shaderów i macierzy, a następnie rysuje piramidę.
 * @param view Macierz widoku.
 * @param projection Macierz projekcji.
 */
void Pyramid::draw(const glm::mat4& view, const glm::mat4& projection)
{
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform4fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(color));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 18);
    glBindVertexArray(0);
}
