#pragma once

#include <iostream>

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