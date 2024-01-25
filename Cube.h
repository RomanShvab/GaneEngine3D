#pragma once

#include "Shape.h"

/**
 * @brief Klasa reprezentująca sześcian dziedzicząca po klasie Shape.
 */
class Cube : public Shape {
public:
    /**
     * @brief Konstruktor domyślny dla klasy Cube.
     * Inicjalizuje sześcian, dziedzicząc konstruktor z klasy Shape.
     */
    Cube();

    /**
     * @brief Czysto wirtualna funkcja rysująca sześcian.
     * @param view Macierz widoku.
     * @param projection Macierz projekcji.
     */
    virtual void draw(const glm::mat4& view, const glm::mat4& projection) override;
};
