#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "Config.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "Render.hpp"
#include "math/Mat4x4.hpp"
#include "math/Triangle.hpp"
#include "math/Vec3d.hpp"
#include "math/Vec2d.hpp"

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

    sf::ConvexShape face;
    sf::VertexArray edge;

    sf::Vector2i windowCenter;
    bool m_isMouseLocked;
    bool m_isPaused;

    Render m_render;
    Camera m_camera;
    Light m_light;

    Mesh m_cube;
    
    float m_cameraTranslateSpeed, m_cameraRotateSpeed;

    sf::Image m_image;
};