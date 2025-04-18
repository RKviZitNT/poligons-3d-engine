#pragma once

#include <initializer_list>
#include <array>
#include <cmath>

#include "utils/ConfigManager.hpp"

class Vec3d;

class Mat4x4 {
public:
    std::array<std::array<float, 4>, 4> m;

    Mat4x4() = default;
    Mat4x4(std::initializer_list<std::initializer_list<float>> values);

    Mat4x4 operator*(const Mat4x4& other) const;

    static Mat4x4 translation(float x, float y, float z);
    static Mat4x4 scale(float scaleX, float scaleY, float scaleZ);
    static Mat4x4 rotationX(float angle);
    static Mat4x4 rotationY(float angle);
    static Mat4x4 rotationZ(float angle);
    static Mat4x4 projection(float fNear, float fFar, float fFov, float fAspectRatio);
    static Mat4x4 pointAt(const Vec3d& pos, const Vec3d& target, const Vec3d& up);
    static Mat4x4 inverse(const Mat4x4& m);
};