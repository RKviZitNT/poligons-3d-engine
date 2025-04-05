#include "Engine.hpp"

Engine::Engine() : m_window(sf::VideoMode({(unsigned int)config.width, (unsigned int)config.height}), "3d render", sf::Style::Titlebar | sf::Style::Close) {
    m_camera = new Camera;
    m_light = new Light;
    m_render = new Render(*m_camera);

    if (config.texturePath != "-") {
        m_cube = new Mesh(config.modelPath, config.texturePath);
    } else {
        m_cube = new Mesh(config.modelPath);
    }
    
    
    m_window.setMouseCursorVisible(!m_isMouseLocked);
    windowCenter = sf::Vector2i(m_window.getSize().x / 2, m_window.getSize().y / 2);

    m_cameraTranslateSpeed = 2;
    m_cameraRotateSpeed = 0.001;

    m_camera->translateY(0.15);
    m_camera->translateX(0.15);
    m_camera->translateZ(1.5);
    m_camera->rotateHorizontal(0.001);

    m_cube->translate({0, 0, 2});
    m_cube->scale({0.2, 0.2, 0.2});
    m_render->addMesh(*m_cube);
    m_light->setDir({0.5, 1, -0.5});
}

void Engine::run() {
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(1.f / (float)config.frameRate);

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
            switchMouseState();
        }

        if (event->is<sf::Event::FocusGained>()) {
            m_isPaused = false;
            switchMouseState();
        }

        if (event->is<sf::Event::KeyPressed>()) {
            auto eventKeyPressed = event->getIf<sf::Event::KeyPressed>();
            if (eventKeyPressed->code == sf::Keyboard::Key::Escape) {
                switchMouseState();
            }
        }
    }

    float translateSpeed = m_cameraTranslateSpeed * deltaTime.asSeconds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { m_camera->translateForwardNoY(translateSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { m_camera->translateLeft(translateSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { m_camera->translateBackNoY(translateSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { m_camera->translateRight(translateSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) { m_camera->translateUp(translateSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)) { m_camera->translateDown(translateSpeed); }

    if (m_isMouseLocked) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
        sf::Vector2i delta = mousePosition - windowCenter;

        if (delta.x != 0) { m_camera->rotateHorizontal(delta.x * m_cameraRotateSpeed); }
        if (delta.y != 0) { m_camera->rotateVertical(-delta.y * m_cameraRotateSpeed); }

        sf::Mouse::setPosition(windowCenter, m_window);
    }
}

void Engine::update() {
    m_render->update();
}

void Engine::draw() {
    m_window.clear(sf::Color::Black);

    m_render->render(m_window, *m_light);

    m_window.display();
}

void Engine::switchMouseState() {
    m_isMouseLocked = !m_isMouseLocked;
    sf::Mouse::setPosition(windowCenter, m_window);
    m_window.setMouseCursorVisible(!m_isMouseLocked);
}