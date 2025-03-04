#pragma once

#include <cmath>

#include "math/Vec3d.hpp"

class Camera {
public:
    Camera();
    Camera(Vec3d direction, Vec3d position);

    Vec3d getPos();
    Vec3d getDir();

    void translateForward(float offset);
    void translateBack(float offset);
    void translateLeft(float offset);
    void translateRight(float offset);
    void translateUp(float offset);
    void translateDown(float offset);

    void rotateRight(float offset);
    void rotateLeft(float offset);
    void rotateUp(float offset);
    void rotateDown(float offset);

private:
    Vec3d pos, dir;
    float fYaw = 1.55;
    float fPitch = 0;

    void update();
};