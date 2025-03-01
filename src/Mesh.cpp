#include "Mesh.hpp"

Mesh::Mesh(const std::string& filename) {
    load(filename);

    m_position = { 0, 0, 0 };
    m_angleX = m_angleY = m_angleZ = 0;
}

void Mesh::load(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open obj file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);
    }

    file.close();
}

void Mesh::parseLine(std::string line) {
    if (line.empty() || line[0] == '#') {
        return;
    }

    std::istringstream ss(line);
    std::string type;
    ss >> type;

    if (type == "v") {
        float x, y, z;
        ss >> x >> y >> z;
        m_vertices.emplace_back(Vec3d(x, y, z));
    }
    
    if (type == "f") {
        int v1, v2, v3;
        ss >> v1 >> v2 >> v3;
        m_poligons.emplace_back(Triangle(m_vertices[v1-1], m_vertices[v2-1], m_vertices[v3-1]));
    }
}

void Mesh::translate(const Vec3d& offset) {
    m_position = m_position + offset;
}

void Mesh::rotate(float angleX, float angleY, float angleZ) {
    m_angleX += angleX;
    m_angleY += angleY;
    m_angleZ += angleZ;
}

std::vector<Triangle> Mesh::getTransformedTriangles() const {
    Mat4x4 matTrans, matRotX, matRotY, matRotZ;

    matTrans = Mat4x4::translation(m_position.x, m_position.y, m_position.z);
    matRotX = Mat4x4::rotationX(m_angleX);
    matRotY = Mat4x4::rotationY(m_angleY);
    matRotZ = Mat4x4::rotationZ(m_angleZ);

    std::vector<Triangle> transformedPolygons;
    for (auto polygon : m_poligons) {
        // polygon *= matTrans;
        // polygon *= matRotX;
        // polygon *= matRotY;
        // polygon *= matRotZ;
        transformedPolygons.emplace_back(polygon);
    }

    return transformedPolygons;
}