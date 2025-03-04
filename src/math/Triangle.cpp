#include "math/Triangle.hpp"

Triangle::Triangle() : p{ Vec3d(), Vec3d(), Vec3d() } {}
Triangle::Triangle(Vec3d p1, Vec3d p2, Vec3d p3) : p{ p1, p2, p3 } {}

void Triangle::translateX(float f) { for (auto& v : p) { v.x += f; } }
void Triangle::translateY(float f) { for (auto& v : p) { v.y += f; } }
void Triangle::translateZ(float f) { for (auto& v : p) { v.z += f; } }

void Triangle::scaleX(float f) { for (auto& v : p) { v.x *= f; } }
void Triangle::scaleY(float f) { for (auto& v : p) { v.y *= f; } }
void Triangle::scaleZ(float f) { for (auto& v : p) { v.z *= f; } }

Vec3d Triangle::getNormal() const {
    Vec3d ab = p[1] - p[0];
    Vec3d ac = p[2] - p[0];
    return ab.crossProd(ac).normalize();
}

void Triangle::projectionDiv() {
    p[0].projectionDiv();
    p[1].projectionDiv();
    p[2].projectionDiv();
}

Triangle& Triangle::operator*=(const Mat4x4& m) {
    *this = *this * m;
    return *this;
}

Triangle operator*(const Triangle& t, const Mat4x4& m) {
    Triangle result;
    result.p[0] = t.p[0] * m;
    result.p[1] = t.p[1] * m;
    result.p[2] = t.p[2] * m;
    return result;
}

Vec3d Triangle::intersectPlane(const Vec3d& plane_p, const Vec3d& plane_n, const Vec3d& lineStart, const Vec3d& lineEnd) {
    Vec3d normalizedPlaneNormal = plane_n.normalize();
    float plane_d = -normalizedPlaneNormal.dotProd(plane_p);

    float ad = lineStart.dotProd(normalizedPlaneNormal);
    float bd = lineEnd.dotProd(normalizedPlaneNormal);

    float t = (-plane_d - ad) / (bd - ad);

    Vec3d lineStartToEnd = lineEnd - lineStart;
    Vec3d lineToIntersect = lineStartToEnd * t;
    return lineStart + lineToIntersect;
}