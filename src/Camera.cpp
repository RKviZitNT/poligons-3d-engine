#include "Camera.hpp"

Camera::Camera() : pos(Vec3d(0)), dir({0, 0, 1}) {}
Camera::Camera(Vec3d direction, Vec3d position = Vec3d(0)) : dir(direction), pos(position) {}