#include "Camera.hpp"

Camera::Camera() : m_direction(Vec3d()) {}
Camera::Camera(Vec3d direction) : m_direction(direction) {}

Vec3d Camera::getDirection() { return m_direction; }