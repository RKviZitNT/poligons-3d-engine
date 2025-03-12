#include "Engine.hpp"

Engine::Engine() :
    m_window(sf::VideoMode({glbl::window::width, glbl::window::height}), "3d render", sf::Style::Titlebar | sf::Style::Close),
    m_isPaused(false),
    m_isMouseLocked(true),
    m_render(m_camera)
    // m_cube("resources/models/mountains.obj")
{
    m_window.setMouseCursorVisible(!m_isMouseLocked);
    windowCenter = sf::Vector2i(m_window.getSize().x / 2, m_window.getSize().y / 2);

    m_cameraTranslateSpeed = 2;
    m_cameraRotateSpeed = 0.001;

    m_cube.translate({0, 0, 2});
    m_cube.scale({0.2, 0.2, 0.2});
    m_render.addMesh(m_cube);
    m_light.setDir({0.8, 1, -0.5});

    if (!m_image.loadFromFile("resources/textures/bedrock.png")) {
        throw std::runtime_error("Failed to load texture");
    }
}

void Engine::run() {
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(1.f / glbl::window::frameRate);

    sf::Time elapsedTimeSinceLastUpdate = sf::Time::Zero;

    sf::Mouse::setPosition(windowCenter, m_window);

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

        if (delta.x != 0) { m_camera.rotateHorizontal(delta.x * m_cameraRotateSpeed); }
        if (delta.y != 0) { m_camera.rotateVertical(-delta.y * m_cameraRotateSpeed); }

        sf::Mouse::setPosition(windowCenter, m_window);
    }
}

void Engine::update() {
    m_render.update();

    m_cube.rotate({1 * deltaTime.asSeconds(), 1 * deltaTime.asSeconds(), 0});
}

void Engine::draw() {
    m_window.clear(sf::Color::Black);

    sf::VertexArray triangles(sf::PrimitiveType::Triangles);
    sf::VertexArray edges(sf::PrimitiveType::Lines);
    sf::Color edgeColor(255, 128, 0);

    std::vector<Triangle> polygons = m_render.render(m_light);

    for (const auto& polygon : polygons) {
        if (glbl::render::textureVisible && polygon.t) {
            Triangle::texturedTriangle(
                polygon.p[0].x, polygon.p[0].y, polygon.t[0].u, polygon.t[0].v, polygon.t[0].w,
                polygon.p[1].x, polygon.p[1].y, polygon.t[1].u, polygon.t[1].v, polygon.t[1].w,
                polygon.p[2].x, polygon.p[2].y, polygon.t[2].u, polygon.t[2].v, polygon.t[2].w,
                &m_image, m_window
            );
        } else {
            sf::Color faceColor(polygon.col.r, polygon.col.g, polygon.col.b);

            if (glbl::render::faceVisible) {
                triangles.append(sf::Vertex{sf::Vector2f(polygon.p[0].x, polygon.p[0].y), faceColor});
                triangles.append(sf::Vertex{sf::Vector2f(polygon.p[1].x, polygon.p[1].y), faceColor});
                triangles.append(sf::Vertex{sf::Vector2f(polygon.p[2].x, polygon.p[2].y), faceColor});
            }
        }
        if (glbl::render::edgeVisible) {
            edges.append(sf::Vertex{sf::Vector2f(polygon.p[0].x, polygon.p[0].y), edgeColor});
            edges.append(sf::Vertex{sf::Vector2f(polygon.p[1].x, polygon.p[1].y), edgeColor});
            edges.append(sf::Vertex{sf::Vector2f(polygon.p[1].x, polygon.p[1].y), edgeColor});
            edges.append(sf::Vertex{sf::Vector2f(polygon.p[2].x, polygon.p[2].y), edgeColor});
            edges.append(sf::Vertex{sf::Vector2f(polygon.p[2].x, polygon.p[2].y), edgeColor});
            edges.append(sf::Vertex{sf::Vector2f(polygon.p[0].x, polygon.p[0].y), edgeColor});
        }
    }

    if (glbl::render::faceVisible && triangles.getVertexCount() > 0) {
        m_window.draw(triangles);
    }

    if (glbl::render::edgeVisible && edges.getVertexCount() > 0) {
        m_window.draw(edges);
    }

    m_window.display();
}