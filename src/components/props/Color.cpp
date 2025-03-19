#include "components/props/Color.hpp"

// Конструктор для оттенков серого
Color::Color(float gray) : r(gray), g(gray), b(gray) {}  // Все компоненты равны gray

// Конструктор с отдельными значениями для r, g, b
Color::Color(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}  // Инициализация компонент

// Перегрузка оператора умножения на яркость
Color Color::operator*(float brightness) {
    if (brightness >= 0 && brightness <= 1) {  // Проверка, что яркость в допустимом диапазоне [0, 1]
        return { r * brightness, g * brightness, b * brightness };  // Умножение компонент на яркость
    }
    return { r, g, b };  // Если яркость вне диапазона, возвращаем исходный цвет
}