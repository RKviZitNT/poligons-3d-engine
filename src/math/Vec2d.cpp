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

#include "math/Vec2d.hpp"

// Конструкторы
Vec2d::Vec2d(float uv) : u(uv), v(uv), w(1) {}  // Инициализация u и v одинаковым значением, w = 1
Vec2d::Vec2d(float u_, float v_) : u(u_), v(v_), w(1) {}  // Инициализация u и v отдельными значениями, w = 1

// Перегрузка операторов для работы с векторами
Vec2d Vec2d::operator+(const Vec2d& other) const { return { u + other.u, v + other.v }; }  // Сложение векторов
Vec2d Vec2d::operator-(const Vec2d& other) const { return { u - other.u, v - other.v }; }  // Вычитание векторов
Vec2d Vec2d::operator*(const Vec2d& other) const { return { u * other.u, v * other.v }; }  // Поэлементное умножение
Vec2d Vec2d::operator/(const Vec2d& other) const { return { u / other.u, v / other.v }; }  // Поэлементное деление

// Перегрузка операторов для работы с вектором и скаляром
Vec2d Vec2d::operator+(const float& f) const { return { u + f, v + f }; }  // Сложение с скаляром
Vec2d Vec2d::operator-(const float& f) const { return { u - f, v - f }; }  // Вычитание скаляра
Vec2d Vec2d::operator*(const float& f) const { return { u * f, v * f }; }  // Умножение на скаляр
Vec2d Vec2d::operator/(const float& f) const { return { u / f, v / f }; }  // Деление на скаляр

Vec2d Vec2d::operator-() const { return { -u, -v }; }  // Унарный минус (инверсия знака)

// Операторы присваивания с операцией
Vec2d& Vec2d::operator+=(const Vec2d& other) { u += other.u; v += other.v; return *this; }  // Прибавление вектора
Vec2d& Vec2d::operator-=(const Vec2d& other) { u -= other.u; v -= other.v; return *this; }  // Вычитание вектора
Vec2d& Vec2d::operator*=(const Vec2d& other) { u *= other.u; v *= other.v; return *this; }  // Поэлементное умножение
Vec2d& Vec2d::operator/=(const Vec2d& other) { u /= other.u; v /= other.v; return *this; }  // Поэлементное деление

Vec2d& Vec2d::operator+=(const float& f) { u += f; v += f; return *this; }  // Прибавление скаляра
Vec2d& Vec2d::operator-=(const float& f) { u -= f; v -= f; return *this; }  // Вычитание скаляра
Vec2d& Vec2d::operator*=(const float& f) { u *= f; v *= f; return *this; }  // Умножение на скаляр
Vec2d& Vec2d::operator/=(const float& f) { u /= f; v /= f; return *this; }  // Деление на скаляр

// Методы для работы с проекциями
void Vec2d::projectionDiv(float w_) { u /= w_; v /= w_; }  // Деление u и v на w (для проекции)
void Vec2d::setW(float w_) { w = w_; }  // Установка значения w

// Метод для нахождения пересечения линии с плоскостью
void Vec2d::intersectPlane(const Vec2d& lineStart, const Vec2d& lineEnd, float& t) {
    u = lineStart.u + t * (lineEnd.u - lineStart.u);  // Интерполяция u
    v = lineStart.v + t * (lineEnd.v - lineStart.v);  // Интерполяция v
    w = lineStart.w + t * (lineEnd.w - lineStart.w);  // Интерполяция w
}