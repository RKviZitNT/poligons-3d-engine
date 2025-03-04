#pragma once

#include "math/Vec3d.hpp"

class Light {
public:
    Light() = default;
    Light(Vec3d direction);

    void setDir(Vec3d direction);
    Vec3d getDir();

private:
    Vec3d dir;
};