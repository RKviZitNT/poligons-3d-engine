#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>

#include "Config.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "DepthBuffer.hpp"
#include "math/Mat4x4.hpp"
#include "math/Vec3d.hpp"
#include "math/Triangle.hpp"

class Render {
public:
    Render(Camera& camera);

    void addMesh(Mesh& mesh);

    void update();
    void render(sf::RenderWindow& window, Light light);

private:
    std::vector<Mesh*> m_renderMeshes;
    Camera& m_camera;

    Mat4x4 matView, matProj;

    DepthBuffer m_depthBuffer;
};