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

#include "math/Vec2d.hpp"

Vec2d::Vec2d(float uv) : u(uv), v(uv), w(1) {}
Vec2d::Vec2d(float u_, float v_) : u(u_), v(v_), w(1) {}

Vec2d Vec2d::operator+(const Vec2d& other) const { return { u + other.u, v + other.v }; }
Vec2d Vec2d::operator-(const Vec2d& other) const { return { u - other.u, v - other.v }; }
Vec2d Vec2d::operator*(const Vec2d& other) const { return { u * other.u, v * other.v }; }
Vec2d Vec2d::operator/(const Vec2d& other) const { return { u / other.u, v / other.v }; }

Vec2d Vec2d::operator+(const float& f) const { return { u + f, v + f }; }
Vec2d Vec2d::operator-(const float& f) const { return { u - f, v - f }; }
Vec2d Vec2d::operator*(const float& f) const { return { u * f, v * f }; }
Vec2d Vec2d::operator/(const float& f) const { return { u / f, v / f }; }

Vec2d Vec2d::operator-() const { return { -u, -v }; }

Vec2d& Vec2d::operator+=(const Vec2d& other) { u += other.u; v += other.v; return *this; }
Vec2d& Vec2d::operator-=(const Vec2d& other) { u -= other.u; v -= other.v; return *this; }
Vec2d& Vec2d::operator*=(const Vec2d& other) { u *= other.u; v *= other.v; return *this; }
Vec2d& Vec2d::operator/=(const Vec2d& other) { u /= other.u; v /= other.v; return *this; }

Vec2d& Vec2d::operator+=(const float& f) { u += f; v += f; return *this; }
Vec2d& Vec2d::operator-=(const float& f) { u -= f; v -= f; return *this; }
Vec2d& Vec2d::operator*=(const float& f) { u *= f; v *= f; return *this; }
Vec2d& Vec2d::operator/=(const float& f) { u /= f; v /= f; return *this; }

void Vec2d::projectionDiv(float w_) { u /= w_; v /= w_; }
void Vec2d::setW(float w_) { w = w_; }

void Vec2d::intersectPlane(const Vec2d& lineStart, const Vec2d& lineEnd, float& t) {
    u = lineStart.u + t * (lineEnd.u - lineStart.u);
    v = lineStart.v + t * (lineEnd.v - lineStart.v);
    w = lineStart.w + t * (lineEnd.w - lineStart.w);
}