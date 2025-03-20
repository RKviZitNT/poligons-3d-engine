#pragma once

class Color {
public:
    float r = 255, g = 255, b = 255;

    Color() = default;
    Color(float gray);
    Color(float r_, float g_, float b_);

    Color operator*(float brightness);
};