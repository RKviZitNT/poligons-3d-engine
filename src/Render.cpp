#include "Render.hpp"

Render::Render() {}

void Render::addMesh(Mesh& mesh) {
    m_renderMeshes.push_back(&mesh);
}

void Render::update(sf::Time& deltaTime) {
    fAspectRatio = (float)glbl::window::height / (float)glbl::window::width;
    fFovRad = 1.f / tanf(glbl::render::fFov * 0.5f / 180.f * glbl::pi);

    fTheta += 0.5f * deltaTime.asSeconds();

    matProj = Mat4x4{
        { fAspectRatio * fFovRad, 0, 0, 0 },
        { 0, fFovRad, 0, 0 },
        { 0, 0, glbl::render::fFar / (glbl::render::fFar - glbl::render::fNear), 1.0f },
        { 0, 0, (-glbl::render::fFar * glbl::render::fNear) / (glbl::render::fFar - glbl::render::fNear), 0 }
    };

    matRotX = Mat4x4{
        { 1, 0, 0, 0 },
        { 0, cosf(fTheta), sinf(fTheta), 0 },
        { 0, -sinf(fTheta), cosf(fTheta), 0 },
        { 0, 0, 0, 1 }
    };

    matRotY = Mat4x4{
        { cosf(fTheta), 0, sinf(fTheta), 0 },
        { 0, 1, 0, 0 },
        { -sinf(fTheta), 0, cosf(fTheta), 0 },
        { 0, 0, 0, 1 }
    };

    matRotZ = Mat4x4{
        { cosf(fTheta), sinf(fTheta), 0, 0 },
        { -sinf(fTheta), cosf(fTheta), 0, 0 },
        { 0, 0, 1, 0 },
        { 0, 0, 0, 1 }
    };
}

void Render::draw(sf::RenderWindow& window) {
    std::vector<Triangle> renderedPoligons;

    Vec3d lightDir = Vec3d(0.f, -1.f, -1.f).normalize();

    for (auto& mesh : m_renderMeshes) {
        std::vector<Triangle> polygons = mesh->getTransformedTriangles();

        for (auto& polygon : polygons) {
            polygon *= matRotX;
            polygon *= matRotY;
            polygon *= matRotZ;

            polygon.translateZ(7.f);

            if (polygon.getNormal().dotProd(polygon.p[0] - Vec3d()) < 0) {
                polygon.intensity = std::max(0.1f, polygon.getNormal().dotProd(lightDir));
    
                Triangle projectedPolygon = polygon;
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

    // std::sort(m_renderedPoligons.begin(), m_renderedPoligons.end(), [](const Triangle& t1, const Triangle& t2) {
    //     return (t1.p[0].z + t1.p[1].z + t1.p[2].z) > (t2.p[0].z + t2.p[1].z + t2.p[2].z);
    // });

    std::sort(renderedPoligons.begin(), renderedPoligons.end(), [](const Triangle& t1, const Triangle& t2) {
        return std::min({t1.p[0].z, t1.p[1].z, t1.p[2].z}) > std::min({t2.p[0].z, t2.p[1].z, t2.p[2].z});
    });

    sf::ConvexShape face(3);
    sf::VertexArray edge(sf::PrimitiveType::LineStrip, 4);
    for (int i = 0; i < 4; i++) {
        edge[i].color = sf::Color::Black;
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