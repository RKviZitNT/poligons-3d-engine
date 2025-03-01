#pragma once

namespace glbl {
    constexpr float pi = 3.14159f;

    namespace window {
        constexpr int width = 1600;
        constexpr int height = 900;

        constexpr int frameRate = 120;
    }

    namespace render {
        constexpr float fNear = 0.1f;
        constexpr float fFar = 1000.f;
        constexpr float fFov = 90.f;
    }
}