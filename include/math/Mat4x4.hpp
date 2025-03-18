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

#pragma once

#include <initializer_list>
#include <array>
#include <cmath>

#include "Config.hpp"

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