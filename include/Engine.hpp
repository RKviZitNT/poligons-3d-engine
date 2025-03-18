/*
Copyright 2025 RKviZitNT

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Config.hpp"
#include "math/Vec3d.hpp"
#include "components/geometry/Mesh.hpp"
#include "components/lightning/Light.hpp"
#include "rendering/Render.hpp"

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

    sf::Vector2i windowCenter;
    bool m_isMouseLocked;
    bool m_isPaused;

    Render m_render;
    Camera m_camera;
    Light m_light;

    Mesh m_cube;
    
    float m_cameraTranslateSpeed, m_cameraRotateSpeed;
};