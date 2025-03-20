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