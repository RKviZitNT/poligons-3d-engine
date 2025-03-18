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

#include "Config.hpp"
#include "math/Vec3d.hpp"

class Camera {
public:
    Camera();
    Camera(Vec3d direction, Vec3d position);

    Vec3d getPos();
    Vec3d getDir();

    void translateX(float offset);
    void translateY(float offset);
    void translateZ(float offset);

    void translateForward(float offset);
    void translateBack(float offset);
    
    void translateForwardNoY(float offset);
    void translateBackNoY(float offset);

    void translateLeft(float offset);
    void translateRight(float offset);

    void translateUp(float offset);
    void translateDown(float offset);

    void rotateHorizontal(float offset);
    void rotateVertical(float offset);

private:
    Vec3d pos, dir;
    float fYaw = glbl::rad;
    float fPitch = 0;

    void update();
};