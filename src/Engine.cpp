#include "Engine.hpp"

#include <iostream>

Engine::Engine() :
    m_window(sf::VideoMode({glbl::window::width, glbl::window::height}), "3d render", sf::Style::Titlebar | sf::Style::Close),
    face(3),
    edge(sf::PrimitiveType::LineStrip, 4),
    m_isPaused(false),
    m_isMouseLocked(true),
    m_render(m_camera),
    m_cube("resources/mountains.obj")
{
    m_window.setMouseCursorVisible(!m_isMouseLocked);
    windowCenter = sf::Vector2i(m_window.getSize().x / 2, m_window.getSize().y / 2);

    for (int i = 0; i < 4; i++) {
        edge[i].color = sf::Color(255, 128, 0);
    }

    m_cameraTranslateSpeed = 2;
    m_cameraRotateSpeed = 0.001;

    m_cube.translate({0, 0, 2});
    m_cube.scale({0.2, 0.2, 0.2});
    m_render.addMesh(m_cube);
    m_light.setDir({1, 1, 0});
}

void Engine::run() {
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(1.f / glbl::window::frameRate);

    sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;

    while (m_window.isOpen()) {
        deltaTime = clock.restart();
        elapsedTimeSinceLastUpdate += deltaTime;
        
        handleEvents();

        if (m_isPaused) { continue; }
        
        update();
        draw();

        sf::Time elapsedTime = clock.getElapsedTime();
        if (elapsedTime < frameTime) {
            sf::sleep(frameTime - elapsedTime);
        }

        if (elapsedTimeSinceLastUpdate >= sf::seconds(0.05f)) {
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
            m_isPaused = true;
        }

        if (event->is<sf::Event::FocusGained>()) {
            m_isPaused = false;
        }

        if (event->is<sf::Event::KeyPressed>()) {
            auto eventKeyPressed = event->getIf<sf::Event::KeyPressed>();
            if (eventKeyPressed->code == sf::Keyboard::Key::Escape) {
                m_isMouseLocked = !m_isMouseLocked;
                sf::Mouse::setPosition(windowCenter, m_window);
                m_window.setMouseCursorVisible(!m_isMouseLocked);
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { m_camera.translateForwardNoY(m_cameraTranslateSpeed * deltaTime.asSeconds()); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { m_camera.translateLeft(m_cameraTranslateSpeed * deltaTime.asSeconds()); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { m_camera.translateBackNoY(m_cameraTranslateSpeed * deltaTime.asSeconds()); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { m_camera.translateRight(m_cameraTranslateSpeed * deltaTime.asSeconds()); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) { m_camera.translateUp(m_cameraTranslateSpeed * deltaTime.asSeconds()); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) { m_camera.translateDown(m_cameraTranslateSpeed * deltaTime.asSeconds()); }

    if (m_isMouseLocked) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
        sf::Vector2i delta = mousePosition - windowCenter;

        if (delta.x != 0) { m_camera.rotateX(delta.x * m_cameraRotateSpeed); }
        if (delta.y != 0) { m_camera.rotateY(-delta.y * m_cameraRotateSpeed); }

        sf::Mouse::setPosition(windowCenter, m_window);
    }
}

void Engine::update() {
    m_render.update();
}

void Engine::draw() {
    m_window.clear(sf::Color::Black);

    std::vector<Triangle> polygons = m_render.render(m_light);
    for (const auto& polygon : polygons) {
        int color = static_cast<int>(255 * polygon.intensity);
        face.setFillColor(sf::Color(color, color, color));

        if (glbl::render::faceVisible) {
            face.setPoint(0, sf::Vector2f(polygon.p[0].x, polygon.p[0].y));
            face.setPoint(1, sf::Vector2f(polygon.p[1].x, polygon.p[1].y));
            face.setPoint(2, sf::Vector2f(polygon.p[2].x, polygon.p[2].y));
            m_window.draw(face);
        }

        if (glbl::render::edgeVisible) {
            edge[0].position = sf::Vector2f(polygon.p[0].x, polygon.p[0].y);
            edge[1].position = sf::Vector2f(polygon.p[1].x, polygon.p[1].y);
            edge[2].position = sf::Vector2f(polygon.p[2].x, polygon.p[2].y);
            edge[3].position = edge[0].position;
            m_window.draw(edge);
        }
    }

    m_window.display();
}