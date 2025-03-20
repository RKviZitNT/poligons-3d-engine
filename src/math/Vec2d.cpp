#include "math/Vec2d.hpp"

Vec2d::Vec2d(float uv) : u(uv), v(uv) {}
Vec2d::Vec2d(float _u, float _v) : u(_u), v(_v) {}

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