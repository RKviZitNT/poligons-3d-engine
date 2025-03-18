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

#include "math/Mat4x4.hpp"
#include "math/Vec3d.hpp"

// Конструктор с инициализацией списком значений
Mat4x4::Mat4x4(std::initializer_list<std::initializer_list<float>> values) {
    int i = 0, j = 0;
    for (const auto& row : values) {  // Проход по строкам
        for (const auto& val : row) {  // Проход по элементам строки
            m[i][j] = val;  // Заполнение матрицы
            j++;
        }
        i++;
        j = 0;
    }
}

// Умножение матриц
Mat4x4 Mat4x4::operator*(const Mat4x4& mat) const {
    Mat4x4 result;
    for (int i = 0; i < 4; ++i) {  // Проход по строкам первой матрицы
        for (int j = 0; j < 4; ++j) {  // Проход по столбцам второй матрицы
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {  // Суммирование произведений элементов
                result.m[i][j] += this->m[i][k] * mat.m[k][j];
            }
        }
    }
    return result;
}

// Матрица перемещения
Mat4x4 Mat4x4::translation(float x, float y, float z) {
    return Mat4x4{
        { 1,  0,  0,  0 },
        { 0,  1,  0,  0 },
        { 0,  0,  1,  0 },
        { x,  y,  z,  1 }
    };
}

// Матрица масштабирования
Mat4x4 Mat4x4::scale(float scaleX, float scaleY, float scaleZ) {
    return Mat4x4{
        { scaleX,  0,       0,       0 },
        { 0,       scaleY,  0,       0 },
        { 0,       0,       scaleZ,  0 },
        { 0,       0,       0,       1 }
    };
}

// Матрица вращения вокруг оси X
Mat4x4 Mat4x4::rotationX(float angle) {
    float s = sinf(angle);  // Синус угла
    float c = cosf(angle);  // Косинус угла
    return Mat4x4{
        { 1,  0,  0,  0 },
        { 0,  c,  s,  0 },
        { 0, -s,  c,  0 },
        { 0,  0,  0,  1 }
    };
}

// Матрица вращения вокруг оси Y
Mat4x4 Mat4x4::rotationY(float angle) {
    float s = sinf(angle);  // Синус угла
    float c = cosf(angle);  // Косинус угла
    return Mat4x4{
        { c,  0,  s,  0 },
        { 0,  1,  0,  0 },
        {-s,  0,  c,  0 },
        { 0,  0,  0,  1 }
    };
}

// Матрица вращения вокруг оси Z
Mat4x4 Mat4x4::rotationZ(float angle) {
    float s = sinf(angle);  // Синус угла
    float c = cosf(angle);  // Косинус угла
    return Mat4x4{
        { c,  s,  0,  0 },
        {-s,  c,  0,  0 },
        { 0,  0,  1,  0 },
        { 0,  0,  0,  1 }
    };
}

// Матрица проекции
Mat4x4 Mat4x4::projection(float fNear, float fFar, float fFov, float fAspectRatio) {
    float fFovRad = 1.f / tanf(fFov * 0.5f * (glbl::pi / 180.f));  // Преобразование угла обзора в радианы
    return Mat4x4{
        { fAspectRatio * fFovRad,  0,        0,                                 0 },
        { 0,                       fFovRad,  0,                                 0 },
        { 0,                       0,        fFar / (fFar - fNear),             1 },
        { 0,                       0,        (-fFar * fNear) / (fFar - fNear),  0 }
    };
}

// Матрица "наведения"
Mat4x4 Mat4x4::pointAt(const Vec3d& pos, const Vec3d& target, const Vec3d& up) {
    Vec3d newForward = (target - pos).normalize();  // Новое направление "вперёд"
    Vec3d newUp = (up - newForward * up.dot(newForward)).normalize();  // Новое направление "вверх"
    Vec3d newRigh = newUp.cross(newForward);  // Новое направление "вправо"

    return Mat4x4{
        { newRigh.x,     newRigh.y,     newRigh.z,     0 },
        { newUp.x,       newUp.y,       newUp.z,       0 },
        { newForward.x,  newForward.y,  newForward.z,  0 },
        { pos.x,         pos.y,         pos.z,         1 }
    };
}

// Обратная матрица
Mat4x4 Mat4x4::inverse(const Mat4x4& mat) {
    Mat4x4 matrix{
        { mat.m[0][0],  mat.m[1][0],  mat.m[2][0],  0 },
        { mat.m[0][1],  mat.m[1][1],  mat.m[2][1],  0 },
        { mat.m[0][2],  mat.m[1][2],  mat.m[2][2],  0 },
        { 0,            0,            0,            1 }
    };
    matrix.m[3][0] = -(mat.m[3][0] * matrix.m[0][0] + mat.m[3][1] * matrix.m[1][0] + mat.m[3][2] * matrix.m[2][0]);
    matrix.m[3][1] = -(mat.m[3][0] * matrix.m[0][1] + mat.m[3][1] * matrix.m[1][1] + mat.m[3][2] * matrix.m[2][1]);
    matrix.m[3][2] = -(mat.m[3][0] * matrix.m[0][2] + mat.m[3][1] * matrix.m[1][2] + mat.m[3][2] * matrix.m[2][2]);
    return matrix;
}