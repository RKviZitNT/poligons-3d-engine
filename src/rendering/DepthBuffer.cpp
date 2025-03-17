#include "rendering/DepthBuffer.hpp"

DepthBuffer::DepthBuffer(int width, int height) { resize(width, height); }

void DepthBuffer::resize(int width, int height) {
    validateDimensions(width, height);
    
    if (width == m_width && height == m_height) return;
    
    m_depthBuffer = std::make_unique<float[]>(width * height);
    m_width = width;
    m_height = height;
    
    clear();
}

void DepthBuffer::clear(float value) noexcept {
    if (m_depthBuffer) { std::fill(m_depthBuffer.get(), m_depthBuffer.get() + m_width * m_height, value); }
}

float& DepthBuffer::operator()(int index) {
    validateCoordinates(index);
    return m_depthBuffer[index];
}

const float& DepthBuffer::operator()(int index) const {
    validateCoordinates(index);
    return m_depthBuffer[index];
}

void DepthBuffer::validateDimensions(int width, int height) const {
    if (width <= 0 || height <= 0) { throw std::invalid_argument("Dimensions must be positive"); }
}

void DepthBuffer::validateCoordinates(int index) const {
    if (index > m_width * m_height || index < 0) { throw std::out_of_range("Invalid coordinates"); }
}