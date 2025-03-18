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

#include "components/geometry/Mesh.hpp"

// Конструктор для загрузки модели без текстуры
Mesh::Mesh(const std::string& modelFilename) {
    loadModel(modelFilename);  // Загрузка модели
    init();  // Инициализация параметров
}

// Конструктор для загрузки модели с текстурой
Mesh::Mesh(const std::string& modelFilename, const std::string& textureFilename) {
    loadModel(modelFilename);  // Загрузка модели
    loadTexture(textureFilename);  // Загрузка текстуры
    init();  // Инициализация параметров
}

// Инициализация параметров модели
void Mesh::init() {
    m_position = Vec3d(0);  // Позиция по умолчанию (0, 0, 0)
    m_scale = Vec3d(1);  // Масштаб по умолчанию (1, 1, 1)
    m_angle = Vec3d(0);  // Углы вращения по умолчанию (0, 0, 0)
}

// Получение текстуры модели
sf::Image* Mesh::getTexture() { return m_texture; }

// Загрузка модели из файла .obj
void Mesh::loadModel(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open obj file: " + filename);  // Ошибка, если файл не открылся
    }

    std::string line;
    while (std::getline(file, line)) {
        parseLine(line);  // Парсинг каждой строки файла
    }

    file.close();
}

// Загрузка текстуры
void Mesh::loadTexture(std::string filename) {
    m_texture = new sf::Image;
    if (!m_texture->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture");  // Ошибка, если текстура не загрузилась
    }
}

// Парсинг строки файла .obj
void Mesh::parseLine(std::string& line) {
    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;  // Чтение префикса строки (v, vt, f и т.д.)

    if (prefix == "v") {  // Вершина
        Vec3d vertex;
        iss >> vertex.x >> vertex.y >> vertex.z;  // Чтение координат вершины
        m_vertices.push_back(vertex);  // Добавление вершины в список
    }

    else if (prefix == "vt") {  // Текстурная координата
        Vec2d texCoord;
        iss >> texCoord.u >> texCoord.v;  // Чтение текстурных координат
        texCoord.v = 1.0f - texCoord.v;  // Инверсия координаты V (для корректного отображения)
        m_textureCoords.push_back(texCoord);  // Добавление текстурной координаты в список
    }

    else if (prefix == "f") {  // Грань (треугольник)
        std::vector<int> vertexIndices;  // Индексы вершин
        std::vector<int> textureIndices; // Индексы текстурных координат
        std::string token;

        while (iss >> token) {  // Чтение токенов (вершина/текстура)
            int vIdx = extractVertexIndex(token);  // Извлечение индекса вершины
            int tIdx = extractTextureIndex(token);  // Извлечение индекса текстуры
            vertexIndices.push_back(vIdx);  // Добавление индекса вершины
            textureIndices.push_back(tIdx);  // Добавление индекса текстуры
        }

        // Формирование треугольников из вершин
        for (size_t i = 1; i + 1 < vertexIndices.size(); ++i) {
            Triangle tri(
                m_vertices[vertexIndices[0]],
                m_vertices[vertexIndices[i]],
                m_vertices[vertexIndices[i + 1]]
            );

            // Установка текстурных координат, если они есть
            if (!textureIndices.empty() && textureIndices[0] != -1) {
                tri.setTextureCoords(
                    m_textureCoords[textureIndices[0]],
                    m_textureCoords[textureIndices[i]],
                    m_textureCoords[textureIndices[i + 1]]
                );
            }

            m_triangles.push_back(tri);  // Добавление треугольника в список
        }
    }
}

// Извлечение индекса вершины из токена
int Mesh::extractVertexIndex(const std::string& token) {
    size_t pos = token.find('/');
    return (pos != std::string::npos) ? std::stoi(token.substr(0, pos)) - 1 : std::stoi(token) - 1;
}

// Извлечение индекса текстуры из токена
int Mesh::extractTextureIndex(const std::string& token) {
    size_t firstSlash = token.find('/');
    if (firstSlash == std::string::npos) return -1;  // Если нет текстуры, возвращаем -1

    size_t secondSlash = token.find('/', firstSlash + 1);
    if (secondSlash == std::string::npos) {
        return std::stoi(token.substr(firstSlash + 1)) - 1;  // Извлечение индекса текстуры
    }

    return std::stoi(token.substr(firstSlash + 1, secondSlash - firstSlash - 1)) - 1;
}

// Перемещение модели
void Mesh::translate(const Vec3d& offset) {
    m_position += offset;
}

// Масштабирование модели
void Mesh::scale(const Vec3d& scale) {
    m_scale *= scale;
}

// Вращение модели
void Mesh::rotate(const Vec3d& angle) {
    m_angle += angle;
}

// Получение трансформированных треугольников модели
std::vector<Triangle> Mesh::getTransformedTriangles() const {
    Mat4x4 matTrans, matScl, matRot;

    // Создание матриц трансформации
    matTrans = Mat4x4::translation(m_position.x, m_position.y, m_position.z);  // Матрица перемещения
    matScl = Mat4x4::scale(m_scale.x, m_scale.y, m_scale.z);  // Матрица масштабирования
    matRot = Mat4x4::rotationX(m_angle.x) * Mat4x4::rotationY(m_angle.y) * Mat4x4::rotationZ(m_angle.z);  // Матрица вращения

    std::vector<Triangle> transformedTriangles;
    for (auto triangle : m_triangles) {
        triangle *= matScl;  // Применение масштабирования
        triangle *= matRot;  // Применение вращения
        triangle *= matTrans;  // Применение перемещения
        transformedTriangles.emplace_back(triangle);  // Добавление трансформированного треугольника
    }

    return transformedTriangles;
}