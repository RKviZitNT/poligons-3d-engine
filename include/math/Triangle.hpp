#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Vec2d.hpp"
#include "Vec3d.hpp"
#include "Mat4x4.hpp"
#include "Color.hpp"

class Triangle {
public:
    Vec3d p[3];
    Vec2d t[3];
    Color col;

    bool isTextured = true;

    Triangle();
    Triangle(Vec3d p1, Vec3d p2, Vec3d p3, Color color = Color());
    Triangle(Vec3d p1, Vec3d p2, Vec3d p3, Vec2d t1, Vec2d t2, Vec2d t3);

    void translateX(float f);
    void translateY(float f);
    void translateZ(float f);

    void scaleX(float f);
    void scaleY(float f);
    void scaleZ(float f);

    Vec3d getNormal() const;

    void projectionDiv();

    Triangle operator*(const Mat4x4& mat);

    Triangle& operator*=(const Mat4x4& mat);

    static int clipAgainsPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Triangle& inTri, Triangle& outTri1, Triangle& outTri2);
    static void texturedTriangle(int x1, int y1, float u1, float v1, float w1,
                                 int x2, int y2, float u2, float v2, float w2,
                                 int x3, int y3, float u3, float v3, float w3,
                                 sf::Image *image, sf::RenderWindow& window);
};