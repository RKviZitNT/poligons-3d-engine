#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Config.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "linalg/Mat4x4.hpp"
#include "linalg/Vec3d.hpp"
#include "linalg/Triangle.hpp"

class Render {
public:
    Render();

    void addMesh(Mesh& mesh);
    void update(sf::Time& deltaTime);
    void draw(sf::RenderWindow& window, Camera& camera);

private:
    std::vector<Mesh*> m_renderMeshes;

    float fTheta;
    Mat4x4 matProj, matRotX, matRotY, matRotZ;
};