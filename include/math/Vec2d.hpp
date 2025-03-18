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

class Vec2d {
public:
    float u = 0, v = 0;
    float w = 1;

    Vec2d() = default;
    Vec2d(float uv);
    Vec2d(float u_, float v_);

    Vec2d operator+(const Vec2d& other) const;
    Vec2d operator-(const Vec2d& other) const;
    Vec2d operator*(const Vec2d& other) const;
    Vec2d operator/(const Vec2d& other) const;

    Vec2d operator+(const float& f) const;
    Vec2d operator-(const float& f) const;
    Vec2d operator*(const float& f) const;
    Vec2d operator/(const float& f) const;

    Vec2d operator-() const;

    Vec2d& operator+=(const Vec2d& other);
    Vec2d& operator-=(const Vec2d& other);
    Vec2d& operator*=(const Vec2d& other);
    Vec2d& operator/=(const Vec2d& other);
    
    Vec2d& operator+=(const float& f);
    Vec2d& operator-=(const float& f);
    Vec2d& operator*=(const float& f);
    Vec2d& operator/=(const float& f);

    void projectionDiv(float w_);
    void setW(float w_);

    void intersectPlane(const Vec2d& lineStart, const Vec2d& lineEnd, float& t);
};