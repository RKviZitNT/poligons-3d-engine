#pragma once

class Vec2d {
public:
    float u, v;
    float w;

    Vec2d();
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

private:
};