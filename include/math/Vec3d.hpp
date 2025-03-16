#pragma once

#include <cmath>

#include "Mat4x4.hpp"

class Vec3d {
public:
    float x = 0, y = 0, z = 0;
    float w = 1;
    
    Vec3d() = default;
    Vec3d(float xyz);
    Vec3d(float x_, float y_, float z_);

    Vec3d operator+(const Vec3d& other) const;
    Vec3d operator-(const Vec3d& other) const;
    Vec3d operator*(const Vec3d& other) const;
    Vec3d operator/(const Vec3d& other) const;

    Vec3d operator+(const float& f) const;
    Vec3d operator-(const float& f) const;
    Vec3d operator*(const float& f) const;
    Vec3d operator/(const float& f) const;

    Vec3d operator-() const;
    
    Vec3d& operator+=(const Vec3d& other);
    Vec3d& operator-=(const Vec3d& other);
    Vec3d& operator*=(const Vec3d& other);
    Vec3d& operator/=(const Vec3d& other);
    
    Vec3d& operator+=(const float& f);
    Vec3d& operator-=(const float& f);
    Vec3d& operator*=(const float& f);
    Vec3d& operator/=(const float& f);

    Vec3d operator*(const Mat4x4& mat);

    Vec3d cross(const Vec3d& other) const;
    float dot(const Vec3d& other) const;
    
    float length() const;
    Vec3d normalize() const;

    void projectionDiv();

    void intersectPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Vec3d& lineStart, const Vec3d& lineEnd, float& t);
};