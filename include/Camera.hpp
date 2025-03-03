#pragma once

#include "math/Vec3d.hpp"

class Camera {
public:
    Camera();
    Camera(Vec3d direction, Vec3d position);

    Vec3d pos, dir;
    float fYaw = 1;
    float fPitch = 0;

private:
};