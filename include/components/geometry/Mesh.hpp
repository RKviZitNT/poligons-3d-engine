/*
Copyright 2025 RKviZitNT

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Config.hpp"
#include "math/Mat4x4.hpp"
#include "math/Vec3d.hpp"
#include "math/Vec2d.hpp"
#include "components/geometry/Triangle.hpp"
#include "components/Camera.hpp"
#include "components/props/Color.hpp"

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