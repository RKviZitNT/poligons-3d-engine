#include "Engine.hpp"

#include <iostream>

Engine::Engine() :
    m_window(sf::VideoMode({glbl::window::width, glbl::window::height}), "3d render", sf::Style::Titlebar | sf::Style::Close),
    m_render(m_camera),
    m_cube("resources/ship.obj")
{
    m_cameraTranslateSpeed = 2;
    m_cameraRotateSpeed = 2;

    m_render.addMesh(m_cube);
    m_cube.translate({0, 0, 2});
    m_cube.scale({0.2, 0.2, 0.2});
    m_cube.rotate({0, 0, 10});
}

void Engine::run() {
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(1.f / glbl::window::frameRate);

    sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen()) {
        deltaTime = clock.restart();
        elapsedTimeSinceLastUpdate += deltaTime;
        
        handleEvents();
        if (isPaused) {
            continue;
        }
        update();
        draw();

        sf::Time elapsedTime = clock.getElapsedTime();
        if (elapsedTime < frameTime) {
            sf::sleep(frameTime - elapsedTime);
        }

        if (elapsedTimeSinceLastUpdate >= sf::seconds(0.1f)) {
            float fps = 1.f / deltaTime.asSeconds(); 
            m_window.setTitle("3d render - FPS: " + std::to_string(static_cast<int>(fps)));
            elapsedTimeSinceLastUpdate = sf::Time::Zero;
        }
    }
}

void Engine::handleEvents() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { m_cameraTranslate += { 0,  0,  m_cameraTranslateSpeed }; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { m_cameraTranslate += {-m_cameraTranslateSpeed,  0,  0 }; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { m_cameraTranslate += { 0,  0, -m_cameraTranslateSpeed }; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { m_cameraTranslate += { m_cameraTranslateSpeed,  0,  0 }; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) { m_cameraTranslate += { 0,  m_cameraTranslateSpeed,  0 }; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) { m_cameraTranslate += { 0, -m_cameraTranslateSpeed,  0 }; }     

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) { m_cameraRotate += { 0,  0,  0 }; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) { m_cameraRotate += { 0,  0,  0 }; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) { m_cameraRotate += { 0,  0,  0 }; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) { m_cameraRotate += { 0,  0,  0 }; }

    std::cout << m_camera.pos.x << " " << m_camera.pos.y << " " << m_camera.pos.z << std::endl;
    std::cout << m_camera.dir.x << " " << m_camera.dir.y << " " << m_camera.dir.z << std::endl;

    while (const std::optional event = m_window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_window.close();
        }

        if (event->is<sf::Event::FocusLost>()) {
            isPaused = true;
        }

        if (event->is<sf::Event::FocusGained>()) {
            isPaused = false;
        }
    }
}

void Engine::update() {
    m_camera.pos += m_cameraTranslate * deltaTime.asSeconds();
    m_camera.dir += m_cameraRotate * deltaTime.asSeconds();
    m_cameraTranslate = m_cameraRotate = Vec3d();

    m_render.update(deltaTime);

    //m_cube.rotate({1 * deltaTime.asSeconds(), 1 * deltaTime.asSeconds(), 1 * deltaTime.asSeconds()});
}

void Engine::draw() {
    m_window.clear(sf::Color::Black);

    m_render.draw(m_window);

    m_window.display();
}