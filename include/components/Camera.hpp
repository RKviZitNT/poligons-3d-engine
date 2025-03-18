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

#include <cmath>

#include "Config.hpp"
#include "math/Vec3d.hpp"

// Класс для управления камерой в 3D-пространстве
class Camera {
public:
    Camera() = default;  // Конструктор по умолчанию
    Camera(Vec3d direction, Vec3d position);  // Конструктор с заданием направления и позиции

    // Получение текущей позиции и направления камеры
    Vec3d getPos();  // Возвращает текущую позицию камеры
    Vec3d getDir();  // Возвращает текущее направление камеры (с учётом обновления)

    // Методы для перемещения камеры
    void translateX(float offset);  // Перемещение по оси X
    void translateY(float offset);  // Перемещение по оси Y
    void translateZ(float offset);  // Перемещение по оси Z

    void translateForward(float offset);  // Перемещение вперёд по направлению камеры
    void translateBack(float offset);  // Перемещение назад по направлению камеры

    void translateForwardNoY(float offset);  // Перемещение вперёд без изменения Y (для движения по плоскости)
    void translateBackNoY(float offset);  // Перемещение назад без изменения Y

    void translateLeft(float offset);  // Перемещение влево относительно направления камеры
    void translateRight(float offset);  // Перемещение вправо относительно направления камеры

    void translateUp(float offset);  // Перемещение вверх (по оси Y)
    void translateDown(float offset);  // Перемещение вниз (по оси Y)

    // Методы для вращения камеры
    void rotateHorizontal(float offset);  // Вращение по горизонтали (изменение угла fYaw)
    void rotateVertical(float offset);  // Вращение по вертикали (изменение угла fPitch)

private:
    Vec3d pos = Vec3d(0), dir = Vec3d(0, 0, 1);  // Позиция и направление камеры
    float fYaw = glbl::rad;  // Угол поворота по горизонтали (в радианах)
    float fPitch = 0;  // Угол поворота по вертикали (в радианах)

    void update();  // Обновление направления камеры на основе углов fYaw и fPitch
};