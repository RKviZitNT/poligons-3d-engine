#include "Mesh.hpp"

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
    else if (type == "vt") {
        float u, v;
        ss >> u >> v;
        m_textureCoords.emplace_back(Vec2d(u, v));
    }
    else if (type == "f") {
        std::vector<std::string> faceTokens;
        std::string token;
        while (ss >> token) faceTokens.push_back(token);
        
        if (faceTokens.size() < 3) return;

        // Первый треугольник
        std::vector<int> vertices, texCoords;
        for (size_t i = 0; i < 3; ++i) {
            vertices.push_back(extractVertexIndex(faceTokens[i]));
            texCoords.push_back(extractTextureIndex(faceTokens[i]));
        }

        Triangle tri(
            m_vertices[vertices[0] - 1],
            m_vertices[vertices[1] - 1],
            m_vertices[vertices[2] - 1]
        );

        if (all_of(texCoords.begin(), texCoords.end(), [](int t){ return t > 0; })) {
            tri.setTextureCoords(
                m_textureCoords[texCoords[0] - 1],
                m_textureCoords[texCoords[1] - 1],
                m_textureCoords[texCoords[2] - 1]
            );
        }

        m_triangles.push_back(tri);

        for (size_t i = 3; i < faceTokens.size(); ++i) {
            vertices[1] = vertices[2];
            texCoords[1] = texCoords[2];
            
            vertices[2] = extractVertexIndex(faceTokens[i]);
            texCoords[2] = extractTextureIndex(faceTokens[i]);

            Triangle newTri(
                m_vertices[vertices[0] - 1],
                m_vertices[vertices[1] - 1],
                m_vertices[vertices[2] - 1]
            );

            if (all_of(texCoords.begin(), texCoords.end(), [](int t){ return t > 0; })) {
                newTri.setTextureCoords(
                    m_textureCoords[texCoords[0] - 1],
                    m_textureCoords[texCoords[1] - 1],
                    m_textureCoords[texCoords[2] - 1]
                );
            }

            m_triangles.push_back(newTri);
        }
    }
}

int Mesh::extractVertexIndex(const std::string& token) {
    size_t slashPos = token.find('/');
    if (slashPos == std::string::npos) {
        return std::stoi(token);
    }
    return std::stoi(token.substr(0, slashPos));
}

int Mesh::extractTextureIndex(const std::string& token) {
    size_t firstSlash = token.find('/');
    if (firstSlash == std::string::npos) {
        return -1;
    }

    size_t secondSlash = token.find('/', firstSlash + 1);
    if (secondSlash == std::string::npos) {
        std::string texIndexStr = token.substr(firstSlash + 1);
        if (texIndexStr.empty()) {
            return -1; 
        }
        return std::stoi(texIndexStr);
    }

    return -1;
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