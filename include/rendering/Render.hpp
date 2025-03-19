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