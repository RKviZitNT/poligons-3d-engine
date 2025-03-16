#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Vec2d.hpp"
#include "Vec3d.hpp"
#include "Mat4x4.hpp"
#include "Config.hpp"
#include "Color.hpp"
#include "DepthBuffer.hpp"

class Triangle {
public:
    Vec3d p[3];
    Vec2d t[3];
    Color col;

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