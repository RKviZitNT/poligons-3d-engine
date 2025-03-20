#include "components/geometry/Mesh.hpp"

Mesh::Mesh(const std::string& modelFilename) {
    loadModel(modelFilename);
    init();
}

Mesh::Mesh(const std::string& modelFilename, const std::string& textureFilename) {
    loadModel(modelFilename);
    loadTexture(textureFilename);
    init();
}

void Mesh::init() {
    m_position = Vec3d(0);
    m_scale = Vec3d(1);
    m_angle = Vec3d(0);
}

sf::Image* Mesh::getTexture() { return m_texture; }

void Mesh::loadModel(std::string filename) {
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

void Mesh::loadTexture(std::string filename) {
    m_texture = new sf::Image;
    if (!m_texture->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture");
    }
}

void Mesh::parseLine(std::string& line) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    if (prefix == "v") {
        Vec3d vertex;
        iss >> vertex.x >> vertex.y >> vertex.z;
        m_vertices.push_back(vertex);
    }

    else if (prefix == "vt") {
        Vec2d texCoord;
        iss >> texCoord.u >> texCoord.v;
        texCoord.v = 1.0f - texCoord.v;
        m_textureCoords.push_back(texCoord);
    }

    else if (prefix == "f") {
        std::vector<int> vertexIndices;
        std::vector<int> textureIndices;
        std::string token;

        while (iss >> token) {
            int vIdx = extractVertexIndex(token);
            int tIdx = extractTextureIndex(token);
            vertexIndices.push_back(vIdx);
            textureIndices.push_back(tIdx);
        }

        for (size_t i = 1; i + 1 < vertexIndices.size(); ++i) {
            Triangle tri(
                m_vertices[vertexIndices[0]],
                m_vertices[vertexIndices[i]],
                m_vertices[vertexIndices[i + 1]]
            );

            if (!textureIndices.empty() && textureIndices[0] != -1) {
                tri.setTextureCoords(
                    m_textureCoords[textureIndices[0]],
                    m_textureCoords[textureIndices[i]],
                    m_textureCoords[textureIndices[i + 1]]
                );
            }

            m_triangles.push_back(tri);
        }
    }
}

int Mesh::extractVertexIndex(const std::string& token) {
    size_t pos = token.find('/');
    return (pos != std::string::npos) ? std::stoi(token.substr(0, pos)) - 1 : std::stoi(token) - 1;
}

int Mesh::extractTextureIndex(const std::string& token) {
    size_t firstSlash = token.find('/');
    if (firstSlash == std::string::npos) return -1;

    size_t secondSlash = token.find('/', firstSlash + 1);
    if (secondSlash == std::string::npos) {
        return std::stoi(token.substr(firstSlash + 1)) - 1;
    }

    return std::stoi(token.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
}

void Mesh::translate(const Vec3d& offset) {
    m_position += offset;
}

void Mesh::scale(const Vec3d& scale) {
    m_scale *= scale;
}

void Mesh::rotate(const Vec3d& angle) {
    m_angle += angle;
}

std::vector<Triangle> Mesh::getTransformedTriangles() const {
    Mat4x4 matTrans, matScl, matRot;

    matTrans = Mat4x4::translation(m_position.x, m_position.y, m_position.z);
    matScl = Mat4x4::scale(m_scale.x, m_scale.y, m_scale.z);
    matRot = Mat4x4::rotationX(m_angle.x) * Mat4x4::rotationY(m_angle.y) * Mat4x4::rotationZ(m_angle.z);

    std::vector<Triangle> transformedTriangles;
    for (auto triangle : m_triangles) {
        triangle *= matScl;
        triangle *= matRot;
        triangle *= matTrans;
        transformedTriangles.emplace_back(triangle);
    }

    return transformedTriangles;
}