#pragma once

namespace glbl {
    constexpr float pi = 3.14159f;

    namespace window {
        constexpr int width = 1920;
        constexpr int height = 1080;

        constexpr int frameRate = 165;
    }

    namespace render {
        constexpr float fNear = 0.1f;
        constexpr float fFar = 1000.f;
        constexpr float fFov = 90.f;

        constexpr bool faceVisible = false;
        constexpr bool backFaceVisible = false;
        constexpr bool edgeVisible = true;
    }
}