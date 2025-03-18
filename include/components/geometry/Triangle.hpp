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
#include <array>
#include <algorithm>

#include "Config.hpp"
#include "math/Vec2d.hpp"
#include "math/Vec3d.hpp"
#include "math/Mat4x4.hpp"
#include "components/props/Color.hpp"
#include "rendering/DepthBuffer.hpp"

class Triangle {
public:
    std::array<Vec3d, 3> p;
    std::array<Vec2d, 3> t;

    Color col;
    float illumination;

    Triangle();
    Triangle(Vec3d p1, Vec3d p2, Vec3d p3);

    void setColor(Color color);
    void setTextureCoords(Vec2d t1, Vec2d t2, Vec2d t3);

    void scalingToDisplay();

    Vec3d getNormal() const;

    void projectionDiv();

    Triangle operator*(const Mat4x4& mat);

    Triangle& operator*=(const Mat4x4& mat);
    
    sf::VertexArray texturedTriangle(DepthBuffer& depthBuffer, sf::Image* texture);

    static int clipAgainsPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Triangle& inTri, Triangle& outTri1, Triangle& outTri2);

private:
    void translateX(float f);
    void translateY(float f);
    void translateZ(float f);

    void scaleX(float f);
    void scaleY(float f);
    void scaleZ(float f);
};