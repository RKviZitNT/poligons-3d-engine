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