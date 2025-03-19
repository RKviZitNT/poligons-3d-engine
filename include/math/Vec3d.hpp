#pragma once

#include <cmath>

#include "Mat4x4.hpp"

// Класс для работы с 3D-вектором (x, y, z) и дополнительной компонентой w (для однородных координат)
class Vec3d {
public:
    float x = 0, y = 0, z = 0;  // 3D-координаты
    float w = 1;  // Компонента для однородных координат (по умолчанию 1)

    // Конструкторы
    Vec3d() = default;  // Конструктор по умолчанию
    Vec3d(float xyz);  // Конструктор с одинаковыми значениями для x, y, z
    Vec3d(float x_, float y_, float z_);  // Конструктор с отдельными значениями для x, y, z

    // Перегрузка операторов для работы с векторами
    Vec3d operator+(const Vec3d& other) const;  // Сложение векторов
    Vec3d operator-(const Vec3d& other) const;  // Вычитание векторов
    Vec3d operator*(const Vec3d& other) const;  // Поэлементное умножение
    Vec3d operator/(const Vec3d& other) const;  // Поэлементное деление

    // Перегрузка операторов для работы с вектором и скаляром
    Vec3d operator+(const float& f) const;  // Сложение с скаляром
    Vec3d operator-(const float& f) const;  // Вычитание скаляра
    Vec3d operator*(const float& f) const;  // Умножение на скаляр
    Vec3d operator/(const float& f) const;  // Деление на скаляр

    Vec3d operator-() const;  // Унарный минус (инверсия знака)

    // Операторы присваивания с операцией
    Vec3d& operator+=(const Vec3d& other);  // Прибавление вектора
    Vec3d& operator-=(const Vec3d& other);  // Вычитание вектора
    Vec3d& operator*=(const Vec3d& other);  // Поэлементное умножение
    Vec3d& operator/=(const Vec3d& other);  // Поэлементное деление

    Vec3d& operator+=(const float& f);  // Прибавление скаляра
    Vec3d& operator-=(const float& f);  // Вычитание скаляра
    Vec3d& operator*=(const float& f);  // Умножение на скаляр
    Vec3d& operator/=(const float& f);  // Деление на скаляр

    // Умножение вектора на матрицу 4x4 (для трансформаций)
    Vec3d operator*(const Mat4x4& mat);

    // Векторное и скалярное произведение
    Vec3d cross(const Vec3d& other) const;  // Векторное произведение
    float dot(const Vec3d& other) const;  // Скалярное произведение

    // Длина вектора и нормализация
    float length() const;  // Вычисление длины вектора
    Vec3d normalize() const;  // Нормализация вектора (приведение к длине 1)

    // Проекция (деление на w)
    void projectionDiv();  // Деление x, y, z на w (для проекции)

    // Пересечение линии с плоскостью
    void intersectPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Vec3d& lineStart, const Vec3d& lineEnd, float& t);  // Находит параметр t для точки пересечения
};