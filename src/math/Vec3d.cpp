#include "math/Vec3d.hpp"

// Конструкторы
Vec3d::Vec3d(float xyz) : x(xyz), y(xyz), z(xyz), w(1) {}  // Инициализация x, y, z одинаковым значением, w = 1
Vec3d::Vec3d(float x_, float y_, float z_) : x(x_), y(y_), z(z_), w(1) {}  // Инициализация x, y, z отдельными значениями, w = 1

// Перегрузка операторов для работы с векторами
Vec3d Vec3d::operator+(const Vec3d& other) const { return { x + other.x, y + other.y, z + other.z }; }  // Сложение векторов
Vec3d Vec3d::operator-(const Vec3d& other) const { return { x - other.x, y - other.y, z - other.z }; }  // Вычитание векторов
Vec3d Vec3d::operator*(const Vec3d& other) const { return { x * other.x, y * other.y, z * other.z }; }  // Поэлементное умножение
Vec3d Vec3d::operator/(const Vec3d& other) const { return { x / other.x, y / other.y, z / other.z }; }  // Поэлементное деление

// Перегрузка операторов для работы с вектором и скаляром
Vec3d Vec3d::operator+(const float& f) const { return { x + f, y + f, z + f }; }  // Сложение с скаляром
Vec3d Vec3d::operator-(const float& f) const { return { x - f, y - f, z - f }; }  // Вычитание скаляра
Vec3d Vec3d::operator*(const float& f) const { return { x * f, y * f, z * f }; }  // Умножение на скаляр
Vec3d Vec3d::operator/(const float& f) const { return { x / f, y / f, z / f }; }  // Деление на скаляр

Vec3d Vec3d::operator-() const { return { -x, -y, -z }; }  // Унарный минус (инверсия знака)

// Операторы присваивания с операцией
Vec3d& Vec3d::operator+=(const Vec3d& other) { x += other.x; y += other.y; z += other.z; return *this; }  // Прибавление вектора
Vec3d& Vec3d::operator-=(const Vec3d& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }  // Вычитание вектора
Vec3d& Vec3d::operator*=(const Vec3d& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }  // Поэлементное умножение
Vec3d& Vec3d::operator/=(const Vec3d& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }  // Поэлементное деление

Vec3d& Vec3d::operator+=(const float& f) { x += f; y += f; z += f; return *this; }  // Прибавление скаляра
Vec3d& Vec3d::operator-=(const float& f) { x -= f; y -= f; z -= f; return *this; }  // Вычитание скаляра
Vec3d& Vec3d::operator*=(const float& f) { x *= f; y *= f; z *= f; return *this; }  // Умножение на скаляр
Vec3d& Vec3d::operator/=(const float& f) { x /= f; y /= f; z /= f; return *this; }  // Деление на скаляр

// Умножение вектора на матрицу 4x4 (для трансформаций)
Vec3d Vec3d::operator*(const Mat4x4& mat) {
    Vec3d result;
    result.x = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + w * mat.m[3][0];  // x-компонента результата
    result.y = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + w * mat.m[3][1];  // y-компонента результата
    result.z = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + w * mat.m[3][2];  // z-компонента результата
    result.w = x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + w * mat.m[3][3];  // w-компонента результата
    return result;
}

// Векторное произведение
Vec3d Vec3d::cross(const Vec3d& other) const {
    return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };  // Результат векторного произведения
}

// Скалярное произведение
float Vec3d::dot(const Vec3d& other) const { return x * other.x + y * other.y + z * other.z; }  // Результат скалярного произведения

// Длина вектора
float Vec3d::length() const { return sqrtf(x * x + y * y + z * z); }  // Вычисление длины вектора

// Нормализация вектора
Vec3d Vec3d::normalize() const {
    float len = length();  // Вычисление длины
    if (len > 0) {
        return { x / len, y / len, z / len };  // Возврат нормализованного вектора
    }
    return Vec3d(0);  // Если длина нулевая, возвращаем нулевой вектор
}

// Проекция (деление на w)
void Vec3d::projectionDiv() { x /= w; y /= w; z /= w; }  // Деление x, y, z на w (для проекции)

// Пересечение линии с плоскостью
void Vec3d::intersectPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Vec3d& lineStart, const Vec3d& lineEnd, float& t) {
    Vec3d normalizedPlaneNormal = planeNormal.normalize();  // Нормализация нормали плоскости
    float plane_d = -normalizedPlaneNormal.dot(planePoint);  // Вычисление расстояния до плоскости

    float ad = lineStart.dot(normalizedPlaneNormal);  // Скалярное произведение начала линии и нормали
    float bd = lineEnd.dot(normalizedPlaneNormal);  // Скалярное произведение конца линии и нормали

    t = (-plane_d - ad) / (bd - ad);  // Вычисление параметра t для точки пересечения

    Vec3d lineStartToEnd = lineEnd - lineStart;  // Вектор от начала до конца линии
    Vec3d lineToIntersect = lineStartToEnd * t;  // Вектор до точки пересечения
    *this = lineStart + lineToIntersect;  // Результат — точка пересечения
}