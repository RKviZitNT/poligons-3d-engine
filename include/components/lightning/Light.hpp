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

#include "math/Vec3d.hpp"

// Класс для представления источника света (направленный свет)
class Light {
public:
    Light() = default;  // Конструктор по умолчанию
    Light(Vec3d direction);  // Конструктор с заданием направления света

    // Методы для управления направлением света
    void setDir(Vec3d direction);  // Установка направления света
    Vec3d getDir();  // Получение текущего направления света

private:
    Vec3d dir;  // Направление света (нормализованный вектор)
};