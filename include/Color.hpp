#pragma once

#include <cmath>

class Color {
public:
    float r, g, b;

    Color();
    Color(float gray);
    Color(float r_, float g_, float b_);

    void setBrightness(float brightness);

private:
    float m_r, m_g, m_b;
};