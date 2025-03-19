#include "rendering/DepthBuffer.hpp"

// Конструктор с заданием размеров
DepthBuffer::DepthBuffer(int width, int height) { resize(width, height); }

// Изменение размера буфера
void DepthBuffer::resize(int width, int height) {
    validateDimensions(width, height);  // Проверка корректности размеров

    if (width == m_width && height == m_height) return;  // Если размеры не изменились, выходим

    m_depthBuffer = std::make_unique<float[]>(width * height);  // Создание нового буфера
    m_width = width;  // Обновление ширины
    m_height = height;  // Обновление высоты

    clear();  // Очистка буфера
}

// Очистка буфера
void DepthBuffer::clear(float value) noexcept {
    if (m_depthBuffer) {  // Если буфер существует
        std::fill(m_depthBuffer.get(), m_depthBuffer.get() + m_width * m_height, value);  // Заполнение значением
    }
}

// Доступ к элементу буфера по индексу (неконстантная версия)
float& DepthBuffer::operator()(int index) {
    validateCoordinates(index);  // Проверка корректности индекса
    return m_depthBuffer[index];  // Возврат элемента
}

// Доступ к элементу буфера по индексу (константная версия)
const float& DepthBuffer::operator()(int index) const {
    validateCoordinates(index);  // Проверка корректности индекса
    return m_depthBuffer[index];  // Возврат элемента
}

// Валидация размеров буфера
void DepthBuffer::validateDimensions(int width, int height) const {
    if (width <= 0 || height <= 0) { throw std::invalid_argument("Dimensions must be positive"); }  // Ошибка, если размеры некорректны
}

// Валидация индекса
void DepthBuffer::validateCoordinates(int index) const {
    if (index > m_width * m_height || index < 0) { throw std::out_of_range("Invalid coordinates"); }  // Ошибка, если индекс некорректен
}