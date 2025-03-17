#include "components/lightning/Light.hpp"

Light::Light(Vec3d direction) {
    setDir(direction);
}

void Light::setDir(Vec3d direction) { dir = Vec3d(-direction.x, direction.y, direction.z).normalize(); }
Vec3d Light::getDir() { return dir; }