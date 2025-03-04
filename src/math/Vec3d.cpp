#include "math/Vec3d.hpp"

Vec3d::Vec3d() : x(0), y(0), z(0), w(1) {}
Vec3d::Vec3d(float xyz) : x(xyz), y(xyz), z(xyz), w(1) {}
Vec3d::Vec3d(float x_, float y_, float z_) : x(x_), y(y_), z(z_), w(1) {}

Vec3d Vec3d::operator+(const Vec3d& v) const { return {x + v.x, y + v.y, z + v.z}; }
Vec3d Vec3d::operator-(const Vec3d& v) const { return {x - v.x, y - v.y, z - v.z}; }
Vec3d Vec3d::operator*(const Vec3d& v) const { return {x * v.x, y * v.y, z * v.z}; }
Vec3d Vec3d::operator/(const Vec3d& v) const { return {x / v.x, y / v.y, z / v.z}; }

Vec3d Vec3d::operator+(const float& f) const { return {x + f, y + f, z + f}; }
Vec3d Vec3d::operator-(const float& f) const { return {x - f, y - f, z - f}; }
Vec3d Vec3d::operator*(const float& f) const { return {x * f, y * f, z * f}; }
Vec3d Vec3d::operator/(const float& f) const { return {x / f, y / f, z / f}; }

Vec3d& Vec3d::operator+=(const Vec3d& v) { x += v.x; y += v.y; z += v.z; return *this; }
Vec3d& Vec3d::operator-=(const Vec3d& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
Vec3d& Vec3d::operator*=(const Vec3d& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
Vec3d& Vec3d::operator/=(const Vec3d& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

Vec3d& Vec3d::operator+=(const float& f) { x += f; y += f; z += f; return *this; }
Vec3d& Vec3d::operator-=(const float& f) { x -= f; y -= f; z -= f; return *this; }
Vec3d& Vec3d::operator*=(const float& f) { x *= f; y *= f; z *= f; return *this; }
Vec3d& Vec3d::operator/=(const float& f) { x /= f; y /= f; z /= f; return *this; }

Vec3d Vec3d::crossProd(const Vec3d& v) const { return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x}; }
float Vec3d::dotProd(const Vec3d& v) const { return x * v.x + y * v.y + z * v.z; }

float Vec3d::length() const { return sqrtf(x * x + y * y + z * z); }

Vec3d Vec3d::normalize() const {
    float len = length();
    if (len > 0) {
        return {x / len, y / len, z / len};
    }
    return Vec3d(0);
}

void Vec3d::projectionDiv() { x /= w; y /= w; z /= w; }

Vec3d operator*(const Vec3d& v, const Mat4x4& m) {
    Vec3d result;
    result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + v.w * m.m[3][0];
    result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + v.w * m.m[3][1];
    result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + v.w * m.m[3][2];
    result.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + v.w * m.m[3][3];
    return result;
}