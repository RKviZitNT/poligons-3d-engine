#include "Camera.hpp"
#include <cmath>

Camera::Camera() : pos(Vec3d(0)), dir({0, 0, 1}) {}
Camera::Camera(Vec3d direction, Vec3d position) : dir(direction), pos(position) {}

Vec3d Camera::getPos() { return pos; }
Vec3d Camera::getDir() { update(); return dir; }

void Camera::translateForward(float offset) { pos += dir * offset; }
void Camera::translateBack(float offset) { pos -= dir * offset; }
void Camera::translateLeft(float offset) { pos -= dir.crossProd({0, 1, 0}).normalize() * offset; }
void Camera::translateRight(float offset) { pos += dir.crossProd({0, 1, 0}).normalize() * offset; }
void Camera::translateUp(float offset) { pos.y += offset; }
void Camera::translateDown(float offset) { pos.y -= offset; }

void Camera::rotateRight(float offset) { fYaw += offset; }
void Camera::rotateLeft(float offset) { fYaw -= offset; }
void Camera::rotateUp(float offset) { fPitch += offset; }
void Camera::rotateDown(float offset) { fPitch -= offset; }

void Camera::update() {
    const float maxPith = 1.5707f;
    if (fPitch > maxPith) fPitch = maxPith;
    if (fPitch < -maxPith) fPitch = -maxPith;

    dir = Vec3d(cosf(fYaw) * cosf(fPitch), sinf(fPitch), sinf(fYaw) * cosf(fPitch)).normalize();
}