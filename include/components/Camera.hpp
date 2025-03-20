#pragma once

#include <cmath>

#include "Config.hpp"
#include "math/Vec3d.hpp"

class Camera {
public:
    Camera() = default;
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
    Vec3d pos = Vec3d(0), dir = Vec3d(0, 0, 1);
    float fYaw = glbl::hpi;
    float fPitch = 0;

    void update();
};