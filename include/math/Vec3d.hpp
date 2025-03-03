#pragma once

#include <cmath>

#include "Mat4x4.hpp"

class Vec3d {
public:
    float x, y, z, w;
    
    Vec3d();
    Vec3d(float xyz);
    Vec3d(float x_, float y_, float z_);

    Vec3d operator+(const Vec3d& v) const;
    Vec3d operator-(const Vec3d& v) const;
    Vec3d operator*(const Vec3d& v) const;
    Vec3d operator/(const Vec3d& v) const;

    Vec3d operator+(const float& f) const;
    Vec3d operator-(const float& f) const;
    Vec3d operator*(const float& f) const;
    Vec3d operator/(const float& f) const;

    Vec3d& operator+=(const Vec3d& v);
    Vec3d& operator-=(const Vec3d& v);
    Vec3d& operator*=(const Vec3d& v);
    Vec3d& operator/=(const Vec3d& v);
    
    Vec3d& operator+=(const float& f);
    Vec3d& operator-=(const float& f);
    Vec3d& operator*=(const float& f);
    Vec3d& operator/=(const float& f);
    
    Vec3d crossProd(const Vec3d& v) const;
    float dotProd(const Vec3d& v) const;
    
    float length() const;
    Vec3d normalize() const;

    friend Vec3d operator*(const Vec3d& v, const Mat4x4& m);
};
