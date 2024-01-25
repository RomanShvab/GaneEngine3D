#pragma once

#include "Shape.h"

/**
 * @brief Klasa reprezentująca piramidę dziedzicząca po klasie Shape.
 */
class Pyramid : public Shape {
public:
    /**
     * @brief Konstruktor domyślny dla klasy Pyramid.
     * Inicjalizuje piramidę, dziedzicząc konstruktor z klasy Shape.
     */
    Pyramid();

    /**
     * @brief Czysto wirtualna funkcja rysująca piramidę.
     * @param view Macierz widoku.
     * @param projection Macierz projekcji.
     */
    virtual void draw(const glm::mat4& view, const glm::mat4& projection) override;

private:
    // Brak dodatkowych prywatnych pól
};
