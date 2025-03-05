#include "Camera.hpp"
#include <cmath>

Camera::Camera() : pos(Vec3d(0)), dir({0, 0, 1}) {}
Camera::Camera(Vec3d direction, Vec3d position) : dir(direction), pos(position) {}

Vec3d Camera::getPos() { return pos; }
Vec3d Camera::getDir() { update(); return dir; }

void Camera::translateX(float offset) { pos.x += offset; }
void Camera::translateY(float offset) { pos.y += offset; }
void Camera::translateZ(float offset) { pos.z += offset; }

void Camera::translateForward(float offset) { pos += dir * offset; }
void Camera::translateBack(float offset) { pos -= dir * offset; }

void Camera::translateForwardNoY(float offset) {pos += Vec3d(dir.x, 0, dir.z).normalize() * offset; }
void Camera::translateBackNoY(float offset) { pos -= Vec3d(dir.x, 0, dir.z).normalize() * offset; }

void Camera::translateLeft(float offset) { pos -= dir.crossProd({0, 1, 0}).normalize() * offset; }
void Camera::translateRight(float offset) { pos += dir.crossProd({0, 1, 0}).normalize() * offset; }

void Camera::translateUp(float offset) { translateY(offset); }
void Camera::translateDown(float offset) { translateY(-offset); }

void Camera::rotateX(float offset) { fYaw += offset; }
void Camera::rotateY(float offset) { fPitch += offset; }

// void Camera::rotateAroundPoint(const Vec3d& point, float yawOffset, float pitchOffset) {
//     Vec3d direction = pos - point;
//     float radius = direction.length();

//     fYaw += yawOffset;
//     fPitch += pitchOffset;

//     const float maxPitch = 1.5707f;
//     if (fPitch > maxPitch) fPitch = maxPitch;
//     if (fPitch < -maxPitch) fPitch = -maxPitch;

//     direction = Vec3d(
//         cosf(fYaw) * cosf(fPitch),
//         sinf(fPitch),
//         sinf(fYaw) * cosf(fPitch)
//     ) * radius;

//     pos = point + direction;
//     dir = (point - pos).normalize();
// }

void Camera::update() {
    const float maxPith = 1.5707f;
    if (fPitch > maxPith) fPitch = maxPith;
    if (fPitch < -maxPith) fPitch = -maxPith;

    dir = Vec3d(cosf(fYaw) * cosf(fPitch), sinf(fPitch), sinf(fYaw) * cosf(fPitch)).normalize();
}