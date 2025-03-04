#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Config.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Render.hpp"
#include "math/Mat4x4.hpp"

class Engine {
public:
    Engine();

    void run();
    void handleEvents();
    void update();
    void draw();

private:
    sf::RenderWindow m_window;
    sf::Time deltaTime;

    Render m_render;
    Camera m_camera;
    Light m_light;

    Mesh m_cube;
    
    float m_cameraTranslateSpeed, m_cameraRotateSpeed;

    float fTheta = 0;
    bool isPaused = false;
};