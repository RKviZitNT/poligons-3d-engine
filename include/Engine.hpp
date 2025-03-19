#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Config.hpp"
#include "math/Vec3d.hpp"
#include "components/geometry/Mesh.hpp"
#include "components/lightning/Light.hpp"
#include "rendering/Render.hpp"

// Класс для управления основным циклом приложения (игровым движком)
class Engine {
public:
    Engine();  // Конструктор (инициализация окна, камеры, света и модели)

    void run();  // Основной цикл приложения
    void handleEvents();  // Обработка событий (ввод пользователя)
    void update();  // Обновление состояния игры
    void draw();  // Отрисовка сцены

private:
    sf::RenderWindow m_window;  // Окно приложения
    sf::Time deltaTime;  // Время, прошедшее с последнего кадра

    sf::Vector2i windowCenter;  // Центр окна (для управления камерой мышью)
    bool m_isMouseLocked;  // Флаг, указывающий, заблокирован ли курсор мыши
    bool m_isPaused;  // Флаг, указывающий, находится ли приложение в режиме паузы

    Render m_render;  // Рендерер (отвечает за отрисовку сцены)
    Camera m_camera;  // Камера (управление видом сцены)
    Light m_light;  // Источник света

    Mesh m_cube;  // 3D-модель (куб или уровень)

    float m_cameraTranslateSpeed, m_cameraRotateSpeed;  // Скорость перемещения и вращения камеры
};