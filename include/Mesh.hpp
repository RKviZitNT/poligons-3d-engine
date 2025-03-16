#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Config.hpp"
#include "Camera.hpp"
#include "Color.hpp"
#include "math/Mat4x4.hpp"
#include "math/Vec3d.hpp"
#include "math/Vec2d.hpp"
#include "math/Triangle.hpp"

class Mesh {
public:
    Mesh(const std::string& modelFilename);
    Mesh(const std::string& modelFilename, const std::string& textureFilename);
    
    void init();
    bool isTextured();
    sf::Image* getTexture();

    void translate(const Vec3d& offset);
    void scale(const Vec3d& scale);
    void rotate(const Vec3d& angle);

    std::vector<Triangle> getTransformedTriangles() const;
    
private:
    std::vector<Triangle> m_triangles;
    std::vector<Vec3d> m_vertices;
    std::vector<Vec2d> m_textureCoords;

    Vec3d m_position, m_scale, m_angle;

    sf::Image* m_texture = nullptr;

    void loadModel(std::string filename);
    void loadTexture(std::string filename);

    void parseLine(std::string& line);
    int extractVertexIndex(const std::string& token);
    int extractTextureIndex(const std::string& token);
};