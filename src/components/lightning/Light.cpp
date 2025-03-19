#include "components/lightning/Light.hpp"

// Конструктор с заданием направления света
Light::Light(Vec3d direction) {
    setDir(direction);  // Устанавливаем направление света
}

// Установка направления света
void Light::setDir(Vec3d direction) {
    dir = Vec3d(-direction.x, direction.y, direction.z).normalize();  // Инвертируем x и нормализуем вектор
}

// Получение текущего направления света
Vec3d Light::getDir() { return dir; }