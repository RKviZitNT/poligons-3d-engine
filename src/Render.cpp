#include "Render.hpp"

Render::Render(Camera& camera) : m_camera(camera) {}

void Render::addMesh(Mesh& mesh) {
    m_renderMeshes.emplace_back(&mesh);
}

void Render::update() {
    matProj = Mat4x4::projection(glbl::render::fNear, glbl::render::fFar, glbl::render::fFov, (float)glbl::window::height / (float)glbl::window::width);
    matView = Mat4x4::inverse(Mat4x4::pointAt(m_camera.getPos(), m_camera.getPos() + m_camera.getDir(), {0, 1, 0}));
}

std::vector<Triangle> Render::render(Light light) {
    std::vector<Triangle> projectedPolygons, renderedPolygons;

    for (auto& mesh : m_renderMeshes) {
        std::vector<Triangle> polygons = mesh->getTransformedTriangles();

        for (auto& polygon : polygons) {
            if (glbl::render::backFaceVisible || polygon.getNormal().dotProd(polygon.p[0] - m_camera.getPos()) < 0) {
                polygon.col.setBrightness(std::max(0.15f, polygon.getNormal().dotProd(light.getDir())));
    
                Triangle projectedPolygon = polygon;
                projectedPolygon *= matView;

                int clippedPolygons = 0;
                Triangle clipped[2];
                clippedPolygons = Triangle::clipAgainsPlane({0, 0, 0.1}, {0, 0, 1}, projectedPolygon, clipped[0], clipped[1]);
                for (int i = 0; i < clippedPolygons; i++) {
                    projectedPolygon = clipped[i] * matProj;
                    projectedPolygon.projectionDiv();

                    projectedPolygon.scaleX(-1);
                    projectedPolygon.scaleY(-1);

                    projectedPolygon.translateX(1.f);
                    projectedPolygon.translateY(1.f);
                    projectedPolygon.scaleX(0.5f * glbl::window::width);
                    projectedPolygon.scaleY(0.5f * glbl::window::height);
        
                    projectedPolygons.emplace_back(projectedPolygon);
                }
            }
        }
    }

    std::sort(projectedPolygons.begin(), projectedPolygons.end(), [](const Triangle& t1, const Triangle& t2) {
        return (t1.p[0].z + t1.p[1].z + t1.p[2].z)/3 > (t2.p[0].z + t2.p[1].z + t2.p[2].z)/3;
    });

    for (const auto& polygon : projectedPolygons) {
        Triangle clipped[2];
        std::deque<Triangle> triangles;
        triangles.emplace_back(polygon);
        int newPolygons = 1;
    
        for (int i = 0; i < 4; i++) {
            int poligonsToAdd = 0;
    
            while (newPolygons > 0) {
                Triangle tri = triangles.front();
                triangles.pop_front();
                newPolygons--;
    
                switch (i) {
                case 0: poligonsToAdd = Triangle::clipAgainsPlane({0, 0, 0}, {0, 1, 0}, tri, clipped[0], clipped[1]); break;
                case 1: poligonsToAdd = Triangle::clipAgainsPlane({0, (float)glbl::window::height - 1, 0}, {0, -1, 0}, tri, clipped[0], clipped[1]); break;
                case 2: poligonsToAdd = Triangle::clipAgainsPlane({0, 0, 0}, {1, 0, 0}, tri, clipped[0], clipped[1]); break;
                case 3: poligonsToAdd = Triangle::clipAgainsPlane({(float)glbl::window::width - 1, 0, 0}, {-1, 0, 0}, tri, clipped[0], clipped[1]); break;
                }
    
                for (int j = 0; j < poligonsToAdd; j++) {
                    triangles.push_back(clipped[j]);
                }
            }
    
            newPolygons = triangles.size();
        }
        
        for (const auto& tri : triangles) { renderedPolygons.emplace_back(tri); }
    }

    return renderedPolygons;
}