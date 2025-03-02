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
    Render(Camera& camera);

    void addMesh(Mesh& mesh);
    void update(sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);

private:
    std::vector<Mesh*> m_renderMeshes;
    Camera& m_camera;

    Vec3d lightDir, vUp, vTarget;

    float fTheta;
    Mat4x4 matView, matProj, matRotX, matRotY, matRotZ;
};