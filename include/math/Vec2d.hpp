/*
Copyright 2025 RKviZitNT

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

// Класс для работы с 2D-вектором (u, v) и дополнительной компонентой w (для проекций)
class Vec2d {
public:
    float u = 0, v = 0;  // 2D-координаты
    float w = 1;  // Компонента для однородных координат (по умолчанию 1)

    Vec2d() = default;  // Конструктор по умолчанию
    Vec2d(float uv);  // Конструктор с одинаковыми значениями для u и v
    Vec2d(float u_, float v_);  // Конструктор с отдельными значениями для u и v

    // Перегрузка операторов для работы с векторами
    Vec2d operator+(const Vec2d& other) const;  // Сложение векторов
    Vec2d operator-(const Vec2d& other) const;  // Вычитание векторов
    Vec2d operator*(const Vec2d& other) const;  // Поэлементное умножение
    Vec2d operator/(const Vec2d& other) const;  // Поэлементное деление

    // Перегрузка операторов для работы с вектором и скаляром
    Vec2d operator+(const float& f) const;  // Сложение с скаляром
    Vec2d operator-(const float& f) const;  // Вычитание скаляра
    Vec2d operator*(const float& f) const;  // Умножение на скаляр
    Vec2d operator/(const float& f) const;  // Деление на скаляр

    Vec2d operator-() const;  // Унарный минус (инверсия знака)

    // Операторы присваивания с операцией
    Vec2d& operator+=(const Vec2d& other);  // Прибавление вектора
    Vec2d& operator-=(const Vec2d& other);  // Вычитание вектора
    Vec2d& operator*=(const Vec2d& other);  // Поэлементное умножение
    Vec2d& operator/=(const Vec2d& other);  // Поэлементное деление

    Vec2d& operator+=(const float& f);  // Прибавление скаляра
    Vec2d& operator-=(const float& f);  // Вычитание скаляра
    Vec2d& operator*=(const float& f);  // Умножение на скаляр
    Vec2d& operator/=(const float& f);  // Деление на скаляр

    // Методы для работы с проекциями
    void projectionDiv(float w_);  // Деление u и v на w (для проекции)
    void setW(float w_);  // Установка значения w

    // Метод для нахождения пересечения линии с плоскостью
    void intersectPlane(const Vec2d& lineStart, const Vec2d& lineEnd, float& t);  // Возвращает параметр t для точки пересечения
};