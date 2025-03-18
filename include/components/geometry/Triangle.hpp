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

#include <SFML/Graphics.hpp>
#include <array>
#include <algorithm>

#include "Config.hpp"
#include "math/Vec2d.hpp"
#include "math/Vec3d.hpp"
#include "math/Mat4x4.hpp"
#include "components/props/Color.hpp"
#include "rendering/DepthBuffer.hpp"

// Класс для работы с треугольником в 3D-пространстве
class Triangle {
public:
    std::array<Vec3d, 3> p;  // Вершины треугольника (3D-координаты)
    std::array<Vec2d, 3> t;  // Текстурные координаты для каждой вершины

    Color col;  // Цвет треугольника
    float illumination;  // Освещённость треугольника

    Triangle();  // Конструктор по умолчанию
    Triangle(Vec3d p1, Vec3d p2, Vec3d p3);  // Конструктор с заданием вершин

    void setColor(Color color);  // Установка цвета треугольника
    void setTextureCoords(Vec2d t1, Vec2d t2, Vec2d t3);  // Установка текстурных координат

    void scalingToDisplay();  // Масштабирование треугольника для отображения на экране

    Vec3d getNormal() const;  // Получение нормали треугольника

    void projectionDiv();  // Проецирование треугольника (деление на w)

    Triangle operator*(const Mat4x4& mat);  // Умножение треугольника на матрицу трансформации
    Triangle& operator*=(const Mat4x4& mat);  // Умножение треугольника на матрицу с присваиванием

    sf::VertexArray texturedTriangle(DepthBuffer& depthBuffer, sf::Image* texture);  // Отрисовка текстурированного треугольника

    // Отсечение треугольника относительно плоскости
    static int clipAgainsPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Triangle& inTri, Triangle& outTri1, Triangle& outTri2);

private:
    void translateX(float f);  // Перемещение треугольника по оси X
    void translateY(float f);  // Перемещение треугольника по оси Y
    void translateZ(float f);  // Перемещение треугольника по оси Z

    void scaleX(float f);  // Масштабирование треугольника по оси X
    void scaleY(float f);  // Масштабирование треугольника по оси Y
    void scaleZ(float f);  // Масштабирование треугольника по оси Z
};