/*
Copyright 2025 RKviZitNT

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include <iostream>

namespace glbl {
    constexpr float pi = 3.14159265f;
    constexpr float hpi = pi / 2.f - 0.00001f;
    constexpr float rad = 180.f / pi;

    namespace window {
        constexpr int width = 1200;
        constexpr int height = 800;

        constexpr int frameRate = 10000;
    }

    namespace render {
        constexpr float fNear = 0.1f;
        constexpr float fFar = 1000.f;
        constexpr float fFov = 80.f;

        constexpr bool textureVisible = true;
        constexpr bool faceVisible = true;
        constexpr bool backFaceVisible = true;
        constexpr bool edgeVisible = false;

        constexpr bool liteRender = false;
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