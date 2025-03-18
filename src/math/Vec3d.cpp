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

#include "math/Vec3d.hpp"

Vec3d::Vec3d(float xyz) : x(xyz), y(xyz), z(xyz), w(1) {}
Vec3d::Vec3d(float x_, float y_, float z_) : x(x_), y(y_), z(z_), w(1) {}

Vec3d Vec3d::operator+(const Vec3d& other) const { return { x + other.x, y + other.y, z + other.z }; }
Vec3d Vec3d::operator-(const Vec3d& other) const { return { x - other.x, y - other.y, z - other.z }; }
Vec3d Vec3d::operator*(const Vec3d& other) const { return { x * other.x, y * other.y, z * other.z }; }
Vec3d Vec3d::operator/(const Vec3d& other) const { return { x / other.x, y / other.y, z / other.z }; }

Vec3d Vec3d::operator+(const float& f) const { return { x + f, y + f, z + f }; }
Vec3d Vec3d::operator-(const float& f) const { return { x - f, y - f, z - f }; }
Vec3d Vec3d::operator*(const float& f) const { return { x * f, y * f, z * f }; }
Vec3d Vec3d::operator/(const float& f) const { return { x / f, y / f, z / f }; }

Vec3d Vec3d::operator-() const { return { -x, -y, -z }; }

Vec3d& Vec3d::operator+=(const Vec3d& other) { x += other.x; y += other.y; z += other.z; return *this; }
Vec3d& Vec3d::operator-=(const Vec3d& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
Vec3d& Vec3d::operator*=(const Vec3d& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
Vec3d& Vec3d::operator/=(const Vec3d& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

Vec3d& Vec3d::operator+=(const float& f) { x += f; y += f; z += f; return *this; }
Vec3d& Vec3d::operator-=(const float& f) { x -= f; y -= f; z -= f; return *this; }
Vec3d& Vec3d::operator*=(const float& f) { x *= f; y *= f; z *= f; return *this; }
Vec3d& Vec3d::operator/=(const float& f) { x /= f; y /= f; z /= f; return *this; }

Vec3d Vec3d::operator*(const Mat4x4& mat) {
    Vec3d result;
    result.x = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + w * mat.m[3][0];
    result.y = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + w * mat.m[3][1];
    result.z = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + w * mat.m[3][2];
    result.w = x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + w * mat.m[3][3];
    return result;
}

Vec3d Vec3d::cross(const Vec3d& other) const { return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x}; }
float Vec3d::dot(const Vec3d& other) const { return x * other.x + y * other.y + z * other.z; }

float Vec3d::length() const { return sqrtf(x * x + y * y + z * z); }

Vec3d Vec3d::normalize() const {
    float len = length();
    if (len > 0) {
        return {x / len, y / len, z / len};
    }
    return Vec3d(0);
}

void Vec3d::projectionDiv() { x /= w; y /= w; z /= w; }

void Vec3d::intersectPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Vec3d& lineStart, const Vec3d& lineEnd, float& t) {
    Vec3d normalizedPlaneNormal = planeNormal.normalize();
    float plane_d = -normalizedPlaneNormal.dot(planePoint);

    float ad = lineStart.dot(normalizedPlaneNormal);
    float bd = lineEnd.dot(normalizedPlaneNormal);

    t = (-plane_d - ad) / (bd - ad);

    Vec3d lineStartToEnd = lineEnd - lineStart;
    Vec3d lineToIntersect = lineStartToEnd * t;
    *this = lineStart + lineToIntersect;
}