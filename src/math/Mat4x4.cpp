#include "math/Mat4x4.hpp"
#include "math/Vec3d.hpp"

Mat4x4::Mat4x4(std::initializer_list<std::initializer_list<float>> values) {
    int i = 0, j = 0;
    for (const auto& row : values) {
        for (const auto& val : row) {
            m[i][j] = val;
            j++;
        }
        i++;
        j = 0;
    }
}

Mat4x4 Mat4x4::operator*(const Mat4x4& m) const {
    Mat4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += this->m[i][k] * m.m[k][j];
            }
        }
    }
    return result;
}

Mat4x4 Mat4x4::translation(float x, float y, float z) {
    return Mat4x4{
        { 1,  0,  0,  0 },
        { 0,  1,  0,  0 },
        { 0,  0,  1,  0 },
        { x,  y,  z,  1 }
    };
}

Mat4x4 Mat4x4::scale(float scaleX, float scaleY, float scaleZ) {
    return Mat4x4{
        { scaleX,  0,       0,       0 },
        { 0,       scaleY,  0,       0 },
        { 0,       0,       scaleZ,  0 },
        { 0,       0,       0,       1 }
    };
}

Mat4x4 Mat4x4::rotationX(float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    return Mat4x4{
        { 1,  0,  0,  0 },
        { 0,  c,  s,  0 },
        { 0, -s,  c,  0 },
        { 0,  0,  0,  1 }
    };
}

Mat4x4 Mat4x4::rotationY(float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    return Mat4x4{
        { c,  0,  s,  0 },
        { 0,  1,  0,  0 },
        {-s,  0,  c,  0 },
        { 0,  0,  0,  1 }
    };
}

Mat4x4 Mat4x4::rotationZ(float angle) {
    float s = sinf(angle);
    float c = cosf(angle);
    return Mat4x4{
        { c,  s,  0,  0 },
        {-s,  c,  0,  0 },
        { 0,  0,  1,  0 },
        { 0,  0,  0,  1 }
    };
}

Mat4x4 Mat4x4::projection(float fNear, float fFar, float fFov, float fAspectRatio) {
    float fFovRad = 1.f / tanf(fFov * 0.5f * (3.14159265f / 180.f));
    return Mat4x4{
        { fAspectRatio * fFovRad,  0,        0,                                 0 },
        { 0,                       fFovRad,  0,                                 0 },
        { 0,                       0,        fFar / (fFar - fNear),             1 },
        { 0,                       0,        (-fFar * fNear) / (fFar - fNear),  0 }
    };
}

Mat4x4 Mat4x4::pointAt(const Vec3d& pos, const Vec3d& target, const Vec3d& up) {
    Vec3d newForward = (target - pos).normalize();
    Vec3d newUp = (up - newForward * up.dotProd(newForward)).normalize();
    Vec3d newRigh = newUp.crossProd(newForward);

    return Mat4x4{
        { newRigh.x,     newRigh.y,     newRigh.z,     0 },
        { newUp.x,       newUp.y,       newUp.z,       0 },
        { newForward.x,  newForward.y,  newForward.z,  0 },
        { pos.x,         pos.y,         pos.z,         1 }
    };
}

Mat4x4 Mat4x4::inverse(const Mat4x4& m) {
    Mat4x4 matrix{
        { m.m[0][0],  m.m[1][0],  m.m[2][0],  0 },
        { m.m[0][1],  m.m[1][1],  m.m[2][1],  0 },
        { m.m[0][2],  m.m[1][2],  m.m[2][2],  0 },
        { 0,          0,          0,          1 }
    };
    matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
    return matrix;
}