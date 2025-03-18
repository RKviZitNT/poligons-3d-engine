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
#include <vector>
#include <deque>

#include "Config.hpp"
#include "math/Mat4x4.hpp"
#include "math/Vec3d.hpp"
#include "components/geometry/Triangle.hpp"
#include "components/Camera.hpp"
#include "components/geometry/Mesh.hpp"
#include "components/lightning/Light.hpp"
#include "rendering/DepthBuffer.hpp"

// Класс для рендеринга 3D-сцены
class Render {
public:
    Render(Camera& camera);  // Конструктор (принимает камеру)

    void addMesh(Mesh& mesh);  // Добавление модели в список для рендеринга

    void update();  // Обновление матриц вида и проекции
    void render(sf::RenderWindow& window, Light light);  // Отрисовка сцены

private:
    std::vector<Mesh*> m_renderMeshes;  // Список моделей для рендеринга
    Camera& m_camera;  // Камера (для вычисления матриц вида и проекции)

    Mat4x4 matView, matProj;  // Матрицы вида и проекции

    DepthBuffer m_depthBuffer;  // Буфер глубины для корректного отображения перекрытий
};