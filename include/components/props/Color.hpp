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

// Класс для представления цвета в формате RGB
class Color {
public:
    float r = 255, g = 255, b = 255;  // Компоненты цвета (красный, зелёный, синий), по умолчанию белый цвет

    // Конструкторы
    Color() = default;  // Конструктор по умолчанию (белый цвет)
    Color(float gray);  // Конструктор для оттенков серого (r = g = b = gray)
    Color(float r_, float g_, float b_);  // Конструктор с отдельными значениями для r, g, b

    // Перегрузка оператора умножения на яркость
    Color operator*(float brightness);  // Умножение цвета на коэффициент яркости
};