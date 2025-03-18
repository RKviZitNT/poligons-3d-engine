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

#include "Engine.hpp"

// Конструктор
Engine::Engine() :
    m_window(sf::VideoMode({glbl::window::width, glbl::window::height}), "3d render", sf::Style::Titlebar | sf::Style::Close),  // Создание окна
    m_isPaused(false),  // Изначально приложение не на паузе
    m_isMouseLocked(true),  // Курсор мыши заблокирован по умолчанию
    m_render(m_camera),  // Инициализация рендерера с камерой
    m_cube("resources/models/level.obj", "resources/textures/leveltexhigh.png")  // Загрузка модели и текстуры
{
    m_window.setMouseCursorVisible(!m_isMouseLocked);  // Скрытие курсора мыши, если он заблокирован
    windowCenter = sf::Vector2i(m_window.getSize().x / 2, m_window.getSize().y / 2);  // Вычисление центра окна

    m_cameraTranslateSpeed = 2;  // Скорость перемещения камеры
    m_cameraRotateSpeed = 0.001;  // Скорость вращения камеры

    m_cube.translate({0, 0, 2});  // Перемещение модели
    m_cube.scale({0.2, 0.2, 0.2});  // Масштабирование модели
    m_render.addMesh(m_cube);  // Добавление модели в рендерер
    m_light.setDir({0.8, 1, -0.5});  // Установка направления света
}

// Основной цикл приложения
void Engine::run() {
    sf::Clock clock;  // Таймер для измерения времени
    sf::Time frameTime = sf::seconds(1.f / glbl::window::frameRate);  // Время одного кадра

    sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;  // Время с последнего обновления FPS

    sf::Mouse::setPosition(windowCenter, m_window);  // Установка курсора мыши в центр окна

    while (m_window.isOpen()) {  // Основной цикл
        deltaTime = clock.restart();  // Время, прошедшее с последнего кадра
        elapsedTimeSinceLastUpdate += deltaTime;

        handleEvents();  // Обработка событий

        if (m_isPaused) { continue; }  // Пропуск обновления и отрисовки, если приложение на паузе

        update();  // Обновление состояния
        draw();  // Отрисовка сцены

        // Ограничение FPS
        sf::Time elapsedTime = clock.getElapsedTime();
        if (elapsedTime < frameTime) {
            sf::sleep(frameTime - elapsedTime);
        }

        // Обновление заголовка окна (FPS)
        if (elapsedTimeSinceLastUpdate >= sf::seconds(0.05f)) {
            float fps = 1.f / deltaTime.asSeconds(); 
            m_window.setTitle("3d render - FPS: " + std::to_string(static_cast<int>(fps)));
            elapsedTimeSinceLastUpdate = sf::Time::Zero;
        }
    }
}

// Обработка событий
void Engine::handleEvents() {
    while (const std::optional event = m_window.pollEvent()) {  // Обработка всех событий в очереди
        if (event->is<sf::Event::Closed>()) {  // Закрытие окна
            m_window.close();
        }

        if (event->is<sf::Event::FocusLost>()) {  // Потеря фокуса (пауза)
            m_isPaused = true;
        }

        if (event->is<sf::Event::FocusGained>()) {  // Возврат фокуса (снятие паузы)
            m_isPaused = false;
        }

        if (event->is<sf::Event::KeyPressed>()) {  // Нажатие клавиши
            auto eventKeyPressed = event->getIf<sf::Event::KeyPressed>();
            if (eventKeyPressed->code == sf::Keyboard::Key::Escape) {  // Переключение блокировки мыши
                m_isMouseLocked = !m_isMouseLocked;
                sf::Mouse::setPosition(windowCenter, m_window);
                m_window.setMouseCursorVisible(!m_isMouseLocked);
            }
        }
    }

    // Управление камерой с клавиатуры
    float translateSpeed = m_cameraTranslateSpeed * deltaTime.asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { m_camera.translateForwardNoY(translateSpeed); }  // Вперёд
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { m_camera.translateLeft(translateSpeed); }  // Влево
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { m_camera.translateBackNoY(translateSpeed); }  // Назад
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { m_camera.translateRight(translateSpeed); }  // Вправо
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) { m_camera.translateUp(translateSpeed); }  // Вверх
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) { m_camera.translateDown(translateSpeed); }  // Вниз

    // Управление камерой мышью
    if (m_isMouseLocked) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
        sf::Vector2i delta = mousePosition - windowCenter;

        if (delta.x != 0) { m_camera.rotateHorizontal(delta.x * m_cameraRotateSpeed); }  // Вращение по горизонтали
        if (delta.y != 0) { m_camera.rotateVertical(-delta.y * m_cameraRotateSpeed); }  // Вращение по вертикали

        sf::Mouse::setPosition(windowCenter, m_window);  // Возврат курсора в центр окна
    }
}

// Обновление состояния
void Engine::update() {
    m_render.update();  // Обновление рендерера
}

// Отрисовка сцены
void Engine::draw() {
    m_window.clear(sf::Color::Black);  // Очистка экрана

    m_render.render(m_window, m_light);  // Отрисовка сцены

    m_window.display();  // Отображение кадра
}
