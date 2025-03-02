#include "linalg/Triangle.hpp"

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
