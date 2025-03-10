#include "math/Triangle.hpp"

Triangle::Triangle() : p{ Vec3d(), Vec3d(), Vec3d() } {}
Triangle::Triangle(Vec3d p1, Vec3d p2, Vec3d p3, Color color) : p{ p1, p2, p3 }, col(color) {}
Triangle::Triangle(Vec3d p1, Vec3d p2, Vec3d p3, Vec2d t1, Vec2d t2, Vec2d t3) : p{ p1, p2, p3 }, t{ t1, t2, t3 } {}

void Triangle::translateX(float f) { for (auto& v : p) { v.x += f; } }
void Triangle::translateY(float f) { for (auto& v : p) { v.y += f; } }
void Triangle::translateZ(float f) { for (auto& v : p) { v.z += f; } }

void Triangle::scaleX(float f) { for (auto& v : p) { v.x *= f; } }
void Triangle::scaleY(float f) { for (auto& v : p) { v.y *= f; } }
void Triangle::scaleZ(float f) { for (auto& v : p) { v.z *= f; } }

void Triangle::copyPoints(const Triangle& other) { for (int i = 0; i < 3; i++) { p[i] = other.p[i]; } }
void Triangle::copyTex(const Triangle& other) { for (int i = 0; i < 3; i++) { t[i] = other.t[i]; } }

Vec3d Triangle::getNormal() const {
    Vec3d ab = p[1] - p[0];
    Vec3d ac = p[2] - p[0];
    return ab.crossProd(ac).normalize();
}

void Triangle::projectionDiv() {
    p[0].projectionDiv();
    p[1].projectionDiv();
    p[2].projectionDiv();
}

Triangle& Triangle::operator*=(const Mat4x4& m) {
    p[0] = p[0] * m;
    p[1] = p[1] * m;
    p[2] = p[2] * m;
    return *this;
}

Triangle operator*(const Triangle& t, const Mat4x4& m) {
    Triangle result = t;
    result.p[0] = t.p[0] * m;
    result.p[1] = t.p[1] * m;
    result.p[2] = t.p[2] * m;
    return result;
}

int Triangle::clipAgainsPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Triangle& inTri, Triangle& outTri1, Triangle& outTri2) {
    Vec3d normalizedPlaneNormal = planeNormal.normalize();

    auto dist = [&](const Vec3d& point) {
        return normalizedPlaneNormal.dotProd(point) - normalizedPlaneNormal.dotProd(planePoint);
    };

    const Vec3d* insidePoints[3];  
    const Vec3d* outsidePoints[3];
    int insidePointCount = 0, outsidePointCount = 0;

    const Vec2d* insideTex[3];  
    const Vec2d* outsideTex[3];
    int insideTexCount = 0, outsideTexCount = 0;

    float d0 = dist(inTri.p[0]);
    float d1 = dist(inTri.p[1]);
    float d2 = dist(inTri.p[2]);

    if (d0 >= 0) { insidePoints[insidePointCount++] = &inTri.p[0]; insideTex[insideTexCount++] = &inTri.t[0]; }
    else { outsidePoints[outsidePointCount++] = &inTri.p[0]; outsideTex[outsideTexCount++] = &inTri.t[0]; }
    if (d1 >= 0) { insidePoints[insidePointCount++] = &inTri.p[1]; insideTex[insideTexCount++] = &inTri.t[1]; }
    else { outsidePoints[outsidePointCount++] = &inTri.p[1]; outsideTex[outsideTexCount++] = &inTri.t[1]; }
    if (d2 >= 0) { insidePoints[insidePointCount++] = &inTri.p[2]; insideTex[insideTexCount++] = &inTri.t[2]; }
    else { outsidePoints[outsidePointCount++] = &inTri.p[2]; outsideTex[outsideTexCount++] = &inTri.t[2]; }

    if (insidePointCount == 0) {
        return 0;
    }

    if (insidePointCount == 3) {
        outTri1 = inTri;
        return 1;
    }

    if (insidePointCount == 1 && outsidePointCount == 2) {
        float t;

        outTri1 = inTri;

        outTri1.p[0] = *insidePoints[0];
        outTri1.t[0] = *insideTex[0];

        outTri1.p[1] = Vec3d::intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[0], t);
        outTri1.t[1].u = insideTex[0]->u + t * (outsideTex[0]->u - insideTex[0]->u);
        outTri1.t[1].v = insideTex[0]->v + t * (outsideTex[0]->v - insideTex[0]->v);

        outTri1.p[2] = Vec3d::intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[1], t);
        outTri1.t[2].u = insideTex[0]->u + t * (outsideTex[1]->u - insideTex[0]->u);
        outTri1.t[2].v = insideTex[0]->v + t * (outsideTex[1]->v - insideTex[0]->v);

        return 1;
    }

    if (insidePointCount == 2 && outsidePointCount == 1) {
        float t;

        outTri1 = inTri;
        
        outTri1.p[0] = *insidePoints[0];
        outTri1.t[0] = *insideTex[0];

        outTri1.p[1] = *insidePoints[1];
        outTri1.t[1] = *insideTex[1];

        outTri1.p[2] = Vec3d::intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[0], t);
        outTri1.t[2].u = insideTex[0]->u + t * (outsideTex[0]->u - insideTex[0]->u);
        outTri1.t[2].v = insideTex[0]->v + t * (outsideTex[0]->v - insideTex[0]->v);

        outTri2 = inTri;

        outTri2.p[0] = *insidePoints[1];
        outTri2.t[0] = *insideTex[1];

        outTri2.p[1] = outTri1.p[2];
        outTri2.t[1] = outTri1.t[2];

        outTri2.p[2] = Vec3d::intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[1], *outsidePoints[0], t);
        outTri2.t[2].u = insideTex[1]->u + t * (outsideTex[0]->u - insideTex[1]->u);
        outTri2.t[2].v = insideTex[1]->v + t * (outsideTex[0]->v - insideTex[1]->v);

        return 2;
    }

    return true;
}

void Triangle::texturedTriangle(int x1, int y1, int u1, int v1, int x2, int y2, int u2, int v2, int x3, int y3, int u3, int v3, sf::Image *image, sf::RenderWindow& window) {
    // Сортировка вершин по Y
    if (y2 < y1) { std::swap(y1, y2); std::swap(x1, x2); std::swap(u1, u2); std::swap(v1, v2); }
    if (y3 < y1) { std::swap(y1, y3); std::swap(x1, x3); std::swap(u1, u3); std::swap(v1, v3); }
    if (y3 < y2) { std::swap(y2, y3); std::swap(x2, x3); std::swap(u2, u3); std::swap(v2, v3); }

    // Вычисление шагов для интерполяции
    int dy1 = y2 - y1;
    int dx1 = x2 - x1;
    float du1 = u2 - u1;
    float dv1 = v2 - v1;

    int dy2 = y3 - y1;
    int dx2 = x3 - x1;
    float du2 = u3 - u1;
    float dv2 = v3 - v1;

    float texU, texV;

    float daxStep = 0, dbxStep = 0;
    float du1Step = 0, dv1Step = 0;
    float du2Step = 0, dv2Step = 0;

    if (dy1) daxStep = dx1 / (float)std::abs(dy1);
    if (dy2) dbxStep = dx2 / (float)std::abs(dy2);

    if (dy1) du1Step = du1 / (float)std::abs(dy1);
    if (dy1) dv1Step = dv1 / (float)std::abs(dy1);

    if (dy2) du2Step = du2 / (float)std::abs(dy2);
    if (dy2) dv2Step = dv2 / (float)std::abs(dy2);

    // Создаём VertexArray для хранения всех пикселей
    sf::VertexArray pixels(sf::PrimitiveType::Points);

    // Отрисовка верхней части треугольника
    if (dy1) {
        for (int i = y1; i <= y2; i++) {
            int ax = x1 + (float)(i - y1) * daxStep;
            int bx = x1 + (float)(i - y1) * dbxStep;

            float texSu = u1 + (float)(i - y1) * du1Step;
            float texSv = v1 + (float)(i - y1) * dv1Step;

            float texEu = u1 + (float)(i - y1) * du2Step;
            float texEv = v1 + (float)(i - y1) * dv2Step;

            if (ax > bx) { std::swap(ax, bx); std::swap(texSu, texEu); std::swap(texSv, texEv); }

            texU = texSu;
            texV = texSv;

            float tstep = 1.f / ((float)(bx - ax));
            float t = 0.f;

            for (int j = ax; j < bx; j++) {
                texU = (1.f - t) * texSu + t * texEu;
                texV = (1.f - t) * texSv + t * texEv;

                unsigned int u = static_cast<unsigned int>(texU * image->getSize().x) % image->getSize().x;
                unsigned int v = static_cast<unsigned int>(texV * image->getSize().y) % image->getSize().y;

                // Добавляем пиксель в VertexArray
                pixels.append(sf::Vertex{sf::Vector2f(j, i), image->getPixel({u, v})});

                t += tstep;
            }
        }
    }

    // Отрисовка нижней части треугольника
    dy1 = y3 - y2;
    dx1 = x3 - x2;
    du1 = u3 - u2;
    dv1 = v3 - v2;

    if (dy1) daxStep = dx1 / (float)std::abs(dy1);
    if (dy2) dbxStep = dx2 / (float)std::abs(dy2);

    du1Step = 0; dv1Step = 0;
    if (dy1) du1Step = du1 / (float)std::abs(dy1);
    if (dy1) dv1Step = dv1 / (float)std::abs(dy1);

    if (dy1) {
        for (int i = y2; i <= y3; i++) {
            int ax = x2 + (float)(i - y2) * daxStep;
            int bx = x1 + (float)(i - y1) * dbxStep;

            float texSu = u2 + (float)(i - y2) * du1Step;
            float texSv = v2 + (float)(i - y2) * dv1Step;

            float texEu = u1 + (float)(i - y1) * du2Step;
            float texEv = v1 + (float)(i - y1) * dv2Step;

            if (ax > bx) { std::swap(ax, bx); std::swap(texSu, texEu); std::swap(texSv, texEv); }

            texU = texSu;
            texV = texSv;

            float tstep = 1.f / ((float)(bx - ax));
            float t = 0.f;

            for (int j = ax; j < bx; j++) {
                texU = (1.f - t) * texSu + t * texEu;
                texV = (1.f - t) * texSv + t * texEv;
                
                unsigned int u = static_cast<unsigned int>(texU * image->getSize().x) % image->getSize().x;
                unsigned int v = static_cast<unsigned int>(texV * image->getSize().y) % image->getSize().y;

                // Добавляем пиксель в VertexArray
                pixels.append(sf::Vertex{sf::Vector2f(j, i), image->getPixel({u, v})});

                t += tstep;
            }
        }
    }

    // Отрисовка всех пикселей за один вызов
    window.draw(pixels);
}