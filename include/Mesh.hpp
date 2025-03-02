#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Config.hpp"
#include "Camera.hpp"
#include "linalg/Mat4x4.hpp"
#include "linalg/Vec3d.hpp"
#include "linalg/Triangle.hpp"

class Mesh {
public:
    Mesh(const std::string& filename);
    
    void translate(const Vec3d& offset);
    void scale(const Vec3d& scale);
    void rotate(const Vec3d& angle);

    std::vector<Triangle> getTransformedTriangles() const;
    
private:
    std::vector<Triangle> m_poligons;
    std::vector<Vec3d> m_vertices;

    Vec3d m_position, m_scale, m_angle;

    void load(std::string filename);
    void parseLine(std::string line);
};