#pragma once

#include <memory>
#include <stdexcept>
#include <algorithm>

class DepthBuffer {
public:
    DepthBuffer() = default;
    DepthBuffer(int width, int height);
    
    DepthBuffer(const DepthBuffer&) = delete;
    DepthBuffer& operator=(const DepthBuffer&) = delete;
    
    DepthBuffer(DepthBuffer&&) = default;
    DepthBuffer& operator=(DepthBuffer&&) = default;

    void resize(int width, int height);
    void clear(float value = 1.0f) noexcept;
    
    float& operator()(int index);
    const float& operator()(int index) const;
    
    int width() const noexcept { return m_width; }
    int height() const noexcept { return m_height; }

private:
    std::unique_ptr<float[]> m_depthBuffer;
    int m_width = 0;
    int m_height = 0;
    
    void validateDimensions(int width, int height) const;
    void validateCoordinates(int index) const;
};