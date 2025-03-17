#include "components/props/Color.hpp"

Color::Color(float gray) : r(gray), g(gray), b(gray) {}
Color::Color(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}

Color Color::operator*(float brightness) {
    if (brightness >= 0 && brightness <= 1) {
        return { r * brightness, g * brightness, b * brightness };
    }
    return { r, g, b };
}