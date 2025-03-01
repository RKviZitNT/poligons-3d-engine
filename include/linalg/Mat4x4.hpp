#pragma once

#include <initializer_list>
#include <cmath>

class Mat4x4 {
public:
    float m[4][4] = { 0.f };

    Mat4x4() = default;
    Mat4x4(std::initializer_list<std::initializer_list<float>> values);

    static Mat4x4 rotationX(float angle) {
        float s = sinf(angle);
        float c = cosf(angle);
        return Mat4x4{
            { 1,  0,  0,  0 },
            { 0,  c,  s,  0 },
            { 0, -s,  c,  0 },
            { 0,  0,  0,  1 }
        };
    }

    static Mat4x4 rotationY(float angle) {
        float s = sinf(angle);
        float c = cosf(angle);
        return Mat4x4{
            { c,  0, -s,  0 },
            { 0,  1,  0,  0 },
            { s,  0,  c,  0 },
            { 0,  0,  0,  1 }
        };
    }

    static Mat4x4 rotationZ(float angle) {
        float s = sinf(angle);
        float c = cosf(angle);
        return Mat4x4{
            { c,  s,  0,  0 },
            {-s,  c,  0,  0 },
            { 0,  0,  1,  0 },
            { 0,  0,  0,  1 }
        };
    }

    static Mat4x4 translation(float x, float y, float z) {
        return Mat4x4{
            { 1,  0,  0,  x },
            { 0,  1,  0,  y },
            { 0,  0,  1,  z },
            { 0,  0,  0,  1     }
        };
    }
};
