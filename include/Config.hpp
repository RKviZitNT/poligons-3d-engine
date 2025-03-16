#pragma once

#include <iostream>

namespace glbl {
    constexpr float pi = 3.14159f;

    namespace window {
        constexpr int width = 1920;
        constexpr int height = 1080;

        constexpr int frameRate = 10000;
    }

    namespace render {
        constexpr float fNear = 0.1f;
        constexpr float fFar = 1000.f;
        constexpr float fFov = 90.f;

        constexpr bool textureVisible = true;
        constexpr bool faceVisible = true;
        constexpr bool backFaceVisible = false;
        constexpr bool edgeVisible = false;

        constexpr bool lightRender = false;
    }

    inline void debug() {
        std::cout << std::endl;
    }

    template<typename T, typename... Args>
    inline void debug(T first, Args... args) {
        std::cout << first;
        if constexpr (sizeof...(args) > 0) {
            std::cout << ", ";
        }
        debug(args...);
    }
}