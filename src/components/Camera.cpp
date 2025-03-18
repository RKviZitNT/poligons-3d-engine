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

#include "components/Camera.hpp"

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

void Camera::translateLeft(float offset) { pos -= dir.cross({0, 1, 0}).normalize() * offset; }
void Camera::translateRight(float offset) { pos += dir.cross({0, 1, 0}).normalize() * offset; }

void Camera::translateUp(float offset) { translateY(offset); }
void Camera::translateDown(float offset) { translateY(-offset); }

void Camera::rotateHorizontal(float offset) { fYaw += offset; }
void Camera::rotateVertical(float offset) { fPitch += offset; }

void Camera::update() {
    const float maxPith = glbl::rad;
    if (fPitch > maxPith) fPitch = maxPith;
    if (fPitch < -maxPith) fPitch = -maxPith;

    dir = Vec3d(cosf(fYaw) * cosf(fPitch), sinf(fPitch), sinf(fYaw) * cosf(fPitch)).normalize();
}