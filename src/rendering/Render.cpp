#include "rendering/Render.hpp"

Render::Render(Camera& camera) : m_camera(camera), m_depthBuffer(config.width, config.height) {}

void Render::addMesh(Mesh& mesh) {
    m_renderMeshes.emplace_back(&mesh);
}

void Render::update() {
    matView = Mat4x4::inverse(Mat4x4::pointAt(m_camera.getPos(), m_camera.getPos() + m_camera.getDir(), {0, 1, 0}));
    matProj = Mat4x4::projection(config.fNear, config.fFar, config.fFov, (float)config.height / (float)config.width);
}

void Render::render(sf::RenderWindow& window, Light light) {
    std::vector<Triangle> projectedTriangles, renderedTriangles;
    std::vector<sf::VertexArray> texturedTriangles;

    sf::VertexArray drawingTriangles(sf::PrimitiveType::Triangles);
    sf::VertexArray drawingEdges(sf::PrimitiveType::Lines);
    sf::Color edgeColor(255, 128, 0);

    m_depthBuffer.clear(0.f);

    for (auto& mesh : m_renderMeshes) {
        std::vector<Triangle> triangles = mesh->getTransformedTriangles();

        for (auto& triangle : triangles) {
            if (config.backFaceVisible || triangle.getNormal().dot(triangle.p[0] - m_camera.getPos()) < 0) {
                triangle.illumination = std::max(0.3f, triangle.getNormal().dot(light.getDir()));

                Triangle projectedTriangle = triangle;
                projectedTriangle *= matView;

                int clippedTriangles = 0;
                Triangle clipped[2];
                clippedTriangles = Triangle::clipAgainsPlane({0, 0, 0.1}, {0, 0, 1}, projectedTriangle, clipped[0], clipped[1]);
                for (size_t i = 0; i < clippedTriangles; i++) {
                    projectedTriangle = clipped[i] * matProj;

                    projectedTriangle.projectionDiv();
                    projectedTriangle.scalingToDisplay();

                    projectedTriangles.emplace_back(projectedTriangle);
                }
            }
        }

        if (config.liteRender) {
            std::sort(projectedTriangles.begin(), projectedTriangles.end(), [](const Triangle& t1, const Triangle& t2) {
                return (t1.p[0].z + t1.p[1].z + t1.p[2].z)/3 > (t2.p[0].z + t2.p[1].z + t2.p[2].z)/3;
            });
        }

        for (const auto& triangle : projectedTriangles) {
            Triangle clipped[2];
            std::deque<Triangle> triangles;
            triangles.emplace_back(triangle);
            int newTriangles = 1;

            for (size_t i = 0; i < 4; i++) {
                int poligonsToAdd = 0;

                while (newTriangles > 0) {
                    Triangle tri = triangles.front();
                    triangles.pop_front();
                    newTriangles--;

                    switch (i) {
                    case 0: poligonsToAdd = Triangle::clipAgainsPlane({0, 0, 0}, {0, 1, 0}, tri, clipped[0], clipped[1]); break;
                    case 1: poligonsToAdd = Triangle::clipAgainsPlane({0, (float)config.height - 1, 0}, {0, -1, 0}, tri, clipped[0], clipped[1]); break;
                    case 2: poligonsToAdd = Triangle::clipAgainsPlane({0, 0, 0}, {1, 0, 0}, tri, clipped[0], clipped[1]); break;
                    case 3: poligonsToAdd = Triangle::clipAgainsPlane({(float)config.width - 1, 0, 0}, {-1, 0, 0}, tri, clipped[0], clipped[1]); break;
                    }

                    for (int j = 0; j < poligonsToAdd; j++) {
                        triangles.push_back(clipped[j]);
                    }
                }

                newTriangles = triangles.size();
            }

            for (const auto& tri : triangles) { renderedTriangles.emplace_back(tri); }
        }

        if (!config.liteRender) {
            for (auto& triangle : renderedTriangles) {
                texturedTriangles.emplace_back(triangle.texturedTriangle(m_depthBuffer, mesh->getTexture()));
            }
        }
    }

    if (config.liteRender) {
        for (const auto& triangle : renderedTriangles) {
            sf::Color faceColor(triangle.col.r * triangle.illumination, triangle.col.g * triangle.illumination, triangle.col.b * triangle.illumination);

            if (config.faceVisible) {
                drawingTriangles.append(sf::Vertex{sf::Vector2f(triangle.p[0].x, triangle.p[0].y), faceColor});
                drawingTriangles.append(sf::Vertex{sf::Vector2f(triangle.p[1].x, triangle.p[1].y), faceColor});
                drawingTriangles.append(sf::Vertex{sf::Vector2f(triangle.p[2].x, triangle.p[2].y), faceColor});
            }

            if (config.edgeVisible) {
                drawingEdges.append(sf::Vertex{sf::Vector2f(triangle.p[0].x, triangle.p[0].y), edgeColor});
                drawingEdges.append(sf::Vertex{sf::Vector2f(triangle.p[1].x, triangle.p[1].y), edgeColor});
                drawingEdges.append(sf::Vertex{sf::Vector2f(triangle.p[1].x, triangle.p[1].y), edgeColor});
                drawingEdges.append(sf::Vertex{sf::Vector2f(triangle.p[2].x, triangle.p[2].y), edgeColor});
                drawingEdges.append(sf::Vertex{sf::Vector2f(triangle.p[2].x, triangle.p[2].y), edgeColor});
                drawingEdges.append(sf::Vertex{sf::Vector2f(triangle.p[0].x, triangle.p[0].y), edgeColor});
            }
        }

        if (config.faceVisible && drawingTriangles.getVertexCount() > 0) {
            window.draw(drawingTriangles);
        }

        if (config.edgeVisible && drawingEdges.getVertexCount() > 0) {
            window.draw(drawingEdges);
        }
    }
    else {
        for (const auto& pixels : texturedTriangles) {
            window.draw(pixels);
        }
    }
}