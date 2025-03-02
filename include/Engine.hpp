#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Config.hpp"
#include "Mesh.hpp"
#include "Render.hpp"
#include "linalg/Mat4x4.hpp"

class Engine {
public:
    Engine();

    void run();
    void handleEvents();
    void update(sf::Time& deltaTime);
    void draw();

private:
    sf::RenderWindow m_window;

    Render m_render;
    Camera m_camera;

    Mesh m_cube;

    float fTheta = 0;
    bool isPaused = false;
};