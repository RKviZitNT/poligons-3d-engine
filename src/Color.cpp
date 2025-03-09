#include "Color.hpp"

Color::Color() : m_r(255), m_g(255), m_b(255), r(255), g(255), b(255) {}
Color::Color(float gray) : m_r(gray), m_g(gray), m_b(gray), r(gray), g(gray), b(gray) {}
Color::Color(float r_, float g_, float b_) : m_r(r_), m_g(g_), m_b(b_), r(r_), g(g_), b(b_) {}

void Color::setBrightness(float brightness) {
    brightness = std::max(0.0f, std::min(1.0f, brightness));
    r = m_r * brightness;
    g = m_g * brightness;
    b = m_b * brightness;
}