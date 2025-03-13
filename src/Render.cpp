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
    std::vector<Triangle> projectedTriangles, renderedTriangles;

    for (auto& mesh : m_renderMeshes) {
        std::vector<Triangle> triangles = mesh->getTransformedTriangles();

        for (auto& triangle : triangles) {
            if (glbl::render::backFaceVisible || triangle.getNormal().dotProd(triangle.p[0] - m_camera.getPos()) < 0) {
                triangle.col.setBrightness(std::max(0.15f, triangle.getNormal().dotProd(light.getDir())));
    
                Triangle projectedTriangle = triangle;
                projectedTriangle *= matView;

                int clippedTriangles = 0;
                Triangle clipped[2];
                clippedTriangles = Triangle::clipAgainsPlane({0, 0, 0.1}, {0, 0, 1}, projectedTriangle, clipped[0], clipped[1]);
                for (int i = 0; i < clippedTriangles; i++) {
                    projectedTriangle = clipped[i] * matProj;

                    projectedTriangle.t[0].u = projectedTriangle.t[0].u / projectedTriangle.p[0].w;
                    projectedTriangle.t[1].u = projectedTriangle.t[1].u / projectedTriangle.p[1].w;
                    projectedTriangle.t[2].u = projectedTriangle.t[2].u / projectedTriangle.p[2].w;
                    projectedTriangle.t[0].v = projectedTriangle.t[0].v / projectedTriangle.p[0].w;
                    projectedTriangle.t[1].v = projectedTriangle.t[1].v / projectedTriangle.p[1].w;
                    projectedTriangle.t[2].v = projectedTriangle.t[2].v / projectedTriangle.p[2].w;
                    projectedTriangle.t[0].w = 1.f / projectedTriangle.p[0].w;
                    projectedTriangle.t[1].w = 1.f / projectedTriangle.p[1].w;
                    projectedTriangle.t[2].w = 1.f / projectedTriangle.p[2].w;
                    
                    projectedTriangle.projectionDiv();

                    projectedTriangle.scaleX(-1);
                    projectedTriangle.scaleY(-1);

                    projectedTriangle.translateX(1.f);
                    projectedTriangle.translateY(1.f);
                    projectedTriangle.scaleX(0.5f * glbl::window::width);
                    projectedTriangle.scaleY(0.5f * glbl::window::height);
        
                    projectedTriangles.emplace_back(projectedTriangle);
                }
            }
        }
    }

    std::sort(projectedTriangles.begin(), projectedTriangles.end(), [](const Triangle& t1, const Triangle& t2) {
        return (t1.p[0].z + t1.p[1].z + t1.p[2].z)/3 > (t2.p[0].z + t2.p[1].z + t2.p[2].z)/3;
    });

    for (const auto& triangle : projectedTriangles) {
        Triangle clipped[2];
        std::deque<Triangle> triangles;
        triangles.emplace_back(triangle);
        int newTriangles = 1;
    
        for (int i = 0; i < 4; i++) {
            int poligonsToAdd = 0;
    
            while (newTriangles > 0) {
                Triangle tri = triangles.front();
                triangles.pop_front();
                newTriangles--;
    
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
    
            newTriangles = triangles.size();
        }
        
        for (const auto& tri : triangles) { renderedTriangles.emplace_back(tri); }
    }

    return renderedTriangles;
}