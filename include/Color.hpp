#pragma once

#include <cmath>

class Color {
public:
    float r = 255, g = 255, b = 255;

    Color() = default;
    Color(float gray);
    Color(float r_, float g_, float b_);

    void setBrightness(float brightness);

private:
    float m_r = 255, m_g = 255, m_b = 255;
};