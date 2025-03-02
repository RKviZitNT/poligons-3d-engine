#include "Camera.hpp"

Camera::Camera() : pos({0, 0, 0}), dir({0, 0, 1}) {}
Camera::Camera(Vec3d direction) : pos(direction) {}