#pragma once

#include "Vec3d.hpp"
#include "Mat4x4.hpp"

class Triangle {
public:
    Vec3d p[3];
    float intensity;

    Triangle();
    Triangle(Vec3d p1, Vec3d p2, Vec3d p3);

    void translateX(float f);
    void translateY(float f);
    void translateZ(float f);

    void scaleX(float f);
    void scaleY(float f);
    void scaleZ(float f);

    Vec3d getNormal() const;

    void projectionDiv();

    Triangle& operator*=(const Mat4x4& m);

    friend Triangle operator*(const Triangle& t, const Mat4x4& m);

    static Vec3d intersectPlane(const Vec3d& plane_p, const Vec3d& plane_n, const Vec3d& lineStart, const Vec3d& lineEnd);
};