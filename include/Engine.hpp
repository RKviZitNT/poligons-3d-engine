#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "utils/ConfigManager.hpp"
#include "math/Vec3d.hpp"
#include "components/geometry/Mesh.hpp"
#include "components/lightning/Light.hpp"
#include "rendering/Render.hpp"

class Engine {
public:
    Engine();

    void run();

private:
    sf::RenderWindow m_window;
    sf::Time deltaTime;

    sf::Vector2i windowCenter;
    bool m_isMouseLocked = true;
    bool m_isPaused = false;

    Render* m_render;
    Camera* m_camera;
    Light* m_light;
    Mesh* m_cube;

    float m_cameraTranslateSpeed, m_cameraRotateSpeed;

    void handleEvents();
    void update();
    void draw();

    void switchMouseState();
};