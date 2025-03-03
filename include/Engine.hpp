#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Config.hpp"
#include "Mesh.hpp"
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
    
    Vec3d m_cameraTranslate, m_cameraRotate;
    float m_cameraTranslateSpeed, m_cameraRotateSpeed;

    Mesh m_cube;

    float fTheta = 0;
    bool isPaused = false;
};