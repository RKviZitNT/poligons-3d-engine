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

#include <memory>
#include <stdexcept>
#include <algorithm>

// Класс для работы с буфером глубины (Z-буфер)
class DepthBuffer {
public:
    DepthBuffer() = default;  // Конструктор по умолчанию
    DepthBuffer(int width, int height);  // Конструктор с заданием размеров

    // Запрет копирования
    DepthBuffer(const DepthBuffer&) = delete;
    DepthBuffer& operator=(const DepthBuffer&) = delete;

    // Разрешение перемещения
    DepthBuffer(DepthBuffer&&) = default;
    DepthBuffer& operator=(DepthBuffer&&) = default;

    // Изменение размера буфера
    void resize(int width, int height);

    // Очистка буфера (заполнение значением по умолчанию 1.0)
    void clear(float value = 1.0f) noexcept;

    // Доступ к элементам буфера по индексу
    float& operator()(int index);
    const float& operator()(int index) const;

    // Получение размеров буфера
    int width() const noexcept { return m_width; }
    int height() const noexcept { return m_height; }

private:
    std::unique_ptr<float[]> m_depthBuffer;  // Динамический массив для хранения значений глубины
    int m_width = 0;  // Ширина буфера
    int m_height = 0;  // Высота буфера

    // Валидация размеров буфера
    void validateDimensions(int width, int height) const;

    // Валидация индекса
    void validateCoordinates(int index) const;
};