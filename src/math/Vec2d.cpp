#include "math/Vec2d.hpp"

Vec2d::Vec2d() : u(0), v(0), w(1) {}
Vec2d::Vec2d(float uv) : u(uv), v(uv), w(1) {}
Vec2d::Vec2d(float u_, float v_) : u(u_), v(v_), w(1) {}