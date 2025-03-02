#include "Render.hpp"

#include <iostream>

Render::Render(Camera& camera) : m_camera(camera) {}

void Render::addMesh(Mesh& mesh) {
    m_renderMeshes.push_back(&mesh);
}

void Render::update(sf::Time& deltaTime) {
    fTheta += 0.5f * deltaTime.asSeconds();

    matProj = Mat4x4::projection(glbl::render::fNear, glbl::render::fFar, glbl::render::fFov, (float)glbl::window::height / (float)glbl::window::width);
    
    lightDir = Vec3d(0, -1, -1).normalize();

    matView = Mat4x4::inverse(Mat4x4::pointAt(m_camera.pos, m_camera.pos + m_camera.dir, {0, 1, 0}));
}

void Render::draw(sf::RenderWindow& window) {
    std::vector<Triangle> renderedPoligons;

    for (auto& mesh : m_renderMeshes) {
        std::vector<Triangle> polygons = mesh->getTransformedTriangles();

        for (auto& polygon : polygons) {
            if (polygon.getNormal().dotProd(m_camera.dir) < 0) {
                polygon.intensity = std::max(0.1f, polygon.getNormal().dotProd(lightDir));
    
                Triangle projectedPolygon = polygon;
                projectedPolygon *= matView;
                projectedPolygon *= matProj;

                projectedPolygon.translateX(1.f);
                projectedPolygon.translateY(1.f);
                projectedPolygon.scaleX(0.5f * glbl::window::width);
                projectedPolygon.scaleY(0.5f * glbl::window::height);
    
                projectedPolygon.intensity = polygon.intensity;
                renderedPoligons.emplace_back(projectedPolygon);
            }
        }
    }

    // std::sort(renderedPoligons.begin(), renderedPoligons.end(), [](const Triangle& t1, const Triangle& t2) {
    //     return (t1.p[0].z + t1.p[1].z + t1.p[2].z) > (t2.p[0].z + t2.p[1].z + t2.p[2].z);
    // });

    std::sort(renderedPoligons.begin(), renderedPoligons.end(), [](const Triangle& t1, const Triangle& t2) {
        return std::max({ t1.p[0].z, t1.p[1].z, t1.p[2].z }) > std::max({ t2.p[0].z, t2.p[1].z, t2.p[2].z });
    });

    sf::ConvexShape face(3);
    sf::VertexArray edge(sf::PrimitiveType::LineStrip, 4);
    for (int i = 0; i < 4; i++) {
        edge[i].color = sf::Color(255, 128, 0);
    }

    for (const auto& polygon : renderedPoligons) {
        int color = static_cast<int>(255 * polygon.intensity);
        face.setFillColor(sf::Color(color, color, color));

        face.setPoint(0, sf::Vector2f(polygon.p[0].x, polygon.p[0].y));
        face.setPoint(1, sf::Vector2f(polygon.p[1].x, polygon.p[1].y));
        face.setPoint(2, sf::Vector2f(polygon.p[2].x, polygon.p[2].y));
        window.draw(face);

        // edge[0].position = sf::Vector2f(polygon.p[0].x, polygon.p[0].y);
        // edge[1].position = sf::Vector2f(polygon.p[1].x, polygon.p[1].y);
        // edge[2].position = sf::Vector2f(polygon.p[2].x, polygon.p[2].y);
        // edge[3].position = edge[0].position;
        // window.draw(edge);
    }
}