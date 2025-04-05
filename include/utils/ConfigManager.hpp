#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

struct Config {
    // math const
    float pi = 3.14159265f;
    float hpi = pi / 2.f - 0.00001f;
    float rad = pi / 180.f;

    // window
    int width;
    int height;
    int frameRate;

    // render
    float fNear;
    float fFar;
    float fFov;

    bool textureVisible;
    bool faceVisible;
    bool backFaceVisible;
    bool edgeVisible;

    bool liteRender;

    // resources
    std::string modelPath;
    std::string texturePath;
};

extern Config config;

void LoadConfig(const std::string& filename);