#pragma once

#include "linalg/Vec3d.hpp"

class Camera {
public:
    Camera();
    Camera(Vec3d direction);

    Vec3d getDirection();

private:
    Vec3d m_direction;
};