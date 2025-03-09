#include "math/Vec2d.hpp"

Vec2d::Vec2d() : u(0), v(0) {}
Vec2d::Vec2d(float uv) : u(uv), v(uv) {}
Vec2d::Vec2d(float u_, float v_) : u(u_), v(v_) {}