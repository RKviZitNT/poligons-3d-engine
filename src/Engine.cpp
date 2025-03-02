#include "Engine.hpp"

Engine::Engine() :
    m_window(sf::VideoMode({glbl::window::width, glbl::window::height}), "3d render", sf::Style::Titlebar | sf::Style::Close),
    m_cube("resources/ship.obj")
{
    m_render.addMesh(m_cube);
    m_cube.translate(Vec3d(0, 0, 10));
    m_cube.scale(Vec3d(0.2, 0.2, 0.2));
}

void Engine::run() {
    sf::Clock clock;
    sf::Time deltaTime;
    sf::Time frameTime = sf::seconds(1.f / glbl::window::frameRate);

    sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen()) {
        deltaTime = clock.restart();
        elapsedTimeSinceLastUpdate += deltaTime;
        
        handleEvents();
        if (isPaused) {
            continue;
        }
        update(deltaTime);
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

void Engine::update(sf::Time& deltaTime) {
    m_render.update(deltaTime);

    m_cube.rotate(Vec3d(1 * deltaTime.asSeconds(), 1 * deltaTime.asSeconds(), 1 * deltaTime.asSeconds()));
}

void Engine::draw() {
    m_window.clear(sf::Color::Black);

    m_render.draw(m_window, m_camera);

    m_window.display();
}