#include "linalg/Mat4x4.hpp"

Mat4x4::Mat4x4(std::initializer_list<std::initializer_list<float>> values) {
    int i = 0, j = 0;
    for (const auto& row : values) {
        for (const auto& val : row) {
            m[i][j] = val;
            j++;
        }
        i++;
        j = 0;
    }
}
