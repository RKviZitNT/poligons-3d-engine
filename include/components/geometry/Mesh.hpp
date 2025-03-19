#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "Config.hpp"
#include "math/Mat4x4.hpp"
#include "math/Vec3d.hpp"
#include "math/Vec2d.hpp"
#include "components/geometry/Triangle.hpp"
#include "components/Camera.hpp"
#include "components/props/Color.hpp"

// Класс для работы с 3D-моделями (сетками)
class Mesh {
public:
    // Конструкторы
    Mesh(const std::string& modelFilename);  // Загрузка модели из файла
    Mesh(const std::string& modelFilename, const std::string& textureFilename);  // Загрузка модели и текстуры

    void init();  // Инициализация параметров модели (позиция, масштаб, угол)
    bool isTextured();  // Проверка, есть ли текстура у модели
    sf::Image* getTexture();  // Получение текстуры модели

    // Трансформации модели
    void translate(const Vec3d& offset);  // Перемещение модели
    void scale(const Vec3d& scale);  // Масштабирование модели
    void rotate(const Vec3d& angle);  // Вращение модели

    // Получение трансформированных треугольников модели
    std::vector<Triangle> getTransformedTriangles() const;

private:
    std::vector<Triangle> m_triangles;  // Треугольники модели
    std::vector<Vec3d> m_vertices;  // Вершины модели
    std::vector<Vec2d> m_textureCoords; // Текстурные координаты

    Vec3d m_position, m_scale, m_angle; // Позиция, масштаб и углы вращения модели

    sf::Image* m_texture = nullptr;  // Текстура модели

    // Загрузка модели и текстуры
    void loadModel(std::string filename);  // Загрузка модели из файла .obj
    void loadTexture(std::string filename);  // Загрузка текстуры

    // Парсинг строк файла .obj
    void parseLine(std::string& line);  // Обработка строки файла .obj

    // Извлечение индексов вершин и текстурных координат
    int extractVertexIndex(const std::string& token);  // Извлечение индекса вершины
    int extractTextureIndex(const std::string& token);  // Извлечение индекса текстуры
};