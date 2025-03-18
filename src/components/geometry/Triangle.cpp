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

#include "components/geometry/Triangle.hpp"

Triangle::Triangle() : p{ Vec3d(), Vec3d(), Vec3d() } {}
Triangle::Triangle(Vec3d p1, Vec3d p2, Vec3d p3) : p{ p1, p2, p3 } {}

void Triangle::setColor(Color color) { col = color; }
void Triangle::setTextureCoords(Vec2d t1, Vec2d t2, Vec2d t3) {
    t[0] = t1;
    t[1] = t2;
    t[2] = t3;
}

void Triangle::scalingToDisplay() {
    scaleX(-1);
    scaleY(-1);
    translateX(1.f);
    translateY(1.f);
    scaleX(0.5f * glbl::window::width);
    scaleY(0.5f * glbl::window::height);
}

void Triangle::translateX(float f) { for (auto& v : p) { v.x += f; } }
void Triangle::translateY(float f) { for (auto& v : p) { v.y += f; } }
void Triangle::translateZ(float f) { for (auto& v : p) { v.z += f; } }

void Triangle::scaleX(float f) { for (auto& v : p) { v.x *= f; } }
void Triangle::scaleY(float f) { for (auto& v : p) { v.y *= f; } }
void Triangle::scaleZ(float f) { for (auto& v : p) { v.z *= f; } }

Vec3d Triangle::getNormal() const {
    Vec3d ab = p[1] - p[0];
    Vec3d ac = p[2] - p[0];
    return ab.cross(ac).normalize();
}

void Triangle::projectionDiv() {
    for (int i = 0; i < 3; i++) {
        p[i].projectionDiv();
        t[i].projectionDiv(p[i].w);
        t[i].setW(1.f / p[i].w);
    }
}

Triangle Triangle::operator*(const Mat4x4& mat) {
    Triangle result = *this;
    for (int i = 0; i < 3; i++) {
        result.p[i] = p[i] * mat;
    }
    return result;
}

Triangle& Triangle::operator*=(const Mat4x4& mat) {
    for (int i = 0; i < 3; i++) {
        p[i] = p[i] * mat;
    }
    return *this;
}

sf::VertexArray Triangle::texturedTriangle(DepthBuffer& depthBuffer, sf::Image* texture) {
    int   y1 = p[0].y, y2 = p[1].y, y3 = p[2].y;
    int   x1 = p[0].x, x2 = p[1].x, x3 = p[2].x;
    float u1 = t[0].u, u2 = t[1].u, u3 = t[2].u;
    float v1 = t[0].v, v2 = t[1].v, v3 = t[2].v;
    float w1 = t[0].w, w2 = t[1].w, w3 = t[2].w;

    if (y2 < y1) { std::swap(y1, y2); std::swap(x1, x2); std::swap(u1, u2); std::swap(v1, v2); std::swap(w1, w2); }
    if (y3 < y1) { std::swap(y1, y3); std::swap(x1, x3); std::swap(u1, u3); std::swap(v1, v3); std::swap(w1, w3); }
    if (y3 < y2) { std::swap(y2, y3); std::swap(x2, x3); std::swap(u2, u3); std::swap(v2, v3); std::swap(w2, w3); }

    int   dy1 = y2 - y1;
    int   dx1 = x2 - x1;
    float du1 = u2 - u1;
    float dv1 = v2 - v1;
    float dw1 = w2 - w1;

    int   dy2 = y3 - y1;
    int   dx2 = x3 - x1;
    float du2 = u3 - u1;
    float dv2 = v3 - v1;
    float dw2 = w3 - w1;

    float texU, texV, texW;

    float daxStep = 0, dbxStep = 0;
    float du1Step = 0, dv1Step = 0;
    float du2Step = 0, dv2Step = 0;
    float dw1Step = 0, dw2Step = 0;

    if (dy1) daxStep = dx1 / (float)std::abs(dy1);
    if (dy2) dbxStep = dx2 / (float)std::abs(dy2);

    if (dy1) du1Step = du1 / (float)std::abs(dy1);
    if (dy1) dv1Step = dv1 / (float)std::abs(dy1);
    if (dy1) dw1Step = dw1 / (float)std::abs(dy1);

    if (dy2) du2Step = du2 / (float)std::abs(dy2);
    if (dy2) dv2Step = dv2 / (float)std::abs(dy2);
    if (dy2) dw2Step = dw2 / (float)std::abs(dy2);

    sf::VertexArray pixels(sf::PrimitiveType::Points);

    unsigned int texWidth, texHeight;
    sf::Color texCol;
    Color triCol;

    if (texture && glbl::render::textureVisible) {
        texWidth = texture->getSize().x;
        texHeight = texture->getSize().y;
    }
    else {
        triCol = col * illumination;
    }

    if (dy1) {
        for (int i = y1; i <= y2; i++) {
            int ax = x1 + (float)(i - y1) * daxStep;
            int bx = x1 + (float)(i - y1) * dbxStep;

            float texSu = u1 + (float)(i - y1) * du1Step;
            float texSv = v1 + (float)(i - y1) * dv1Step;
            float texSw = w1 + (float)(i - y1) * dw1Step;

            float texEu = u1 + (float)(i - y1) * du2Step;
            float texEv = v1 + (float)(i - y1) * dv2Step;
            float texEw = w1 + (float)(i - y1) * dw2Step;

            if (ax > bx) { std::swap(ax, bx); std::swap(texSu, texEu); std::swap(texSv, texEv); std::swap(texSw, texEw); }

            texU = texSu;
            texV = texSv;
            texW = texSw;

            float tstep = 1.f / ((float)(bx - ax));
            float t = 0.f;

            for (int j = ax; j < bx; j++) {
                texU = (1.f - t) * texSu + t * texEu;
                texV = (1.f - t) * texSv + t * texEv;
                texW = (1.f - t) * texSw + t * texEw;

                float wInv = 1.0f / texW;

                if (texW > depthBuffer(i * glbl::window::width + j)) {
                    if (texture && glbl::render::textureVisible) {   
                        unsigned int u = static_cast<unsigned int>(std::clamp(texU * wInv * texWidth, 0.0f, static_cast<float>(texWidth-1)));
                        unsigned int v = static_cast<unsigned int>(std::clamp(texV * wInv * texHeight, 0.0f, static_cast<float>(texHeight-1)));

                        texCol = texture->getPixel({u, v});
                        pixels.append(sf::Vertex{sf::Vector2f(j, i), sf::Color(texCol.r * illumination, texCol.g * illumination, texCol.b * illumination)});
                    } else {
                        pixels.append(sf::Vertex{sf::Vector2f(j, i), sf::Color(triCol.r, triCol.g, triCol.b)});
                    }

                    depthBuffer(i * glbl::window::width + j) = texW;
                }

                t += tstep;
            }
        }
    }

    dy1 = y3 - y2;
    dx1 = x3 - x2;
    du1 = u3 - u2;
    dv1 = v3 - v2;
    dw1 = w3 - w2;

    if (dy1) daxStep = dx1 / (float)std::abs(dy1);
    if (dy2) dbxStep = dx2 / (float)std::abs(dy2);

    du1Step = 0; dv1Step = 0;
    if (dy1) du1Step = du1 / (float)std::abs(dy1);
    if (dy1) dv1Step = dv1 / (float)std::abs(dy1);
    if (dy1) dw1Step = dw1 / (float)std::abs(dy1);

    if (dy1) {
        for (int i = y2; i <= y3; i++) {
            int ax = x2 + (float)(i - y2) * daxStep;
            int bx = x1 + (float)(i - y1) * dbxStep;

            float texSu = u2 + (float)(i - y2) * du1Step;
            float texSv = v2 + (float)(i - y2) * dv1Step;
            float texSw = w2 + (float)(i - y2) * dw1Step;

            float texEu = u1 + (float)(i - y1) * du2Step;
            float texEv = v1 + (float)(i - y1) * dv2Step;
            float texEw = w1 + (float)(i - y1) * dw2Step;

            if (ax > bx) { std::swap(ax, bx); std::swap(texSu, texEu); std::swap(texSv, texEv); std::swap(texSw, texEw); }

            texU = texSu;
            texV = texSv;
            texW = texSw;

            float tstep = 1.f / ((float)(bx - ax));
            float t = 0.f;

            for (int j = ax; j < bx; j++) {
                texU = (1.f - t) * texSu + t * texEu;
                texV = (1.f - t) * texSv + t * texEv;
                texW = (1.f - t) * texSw + t * texEw;
                
                float wInv = 1.0f / texW;
                
                if (texW > depthBuffer(i * glbl::window::width + j)) {
                    if (texture && glbl::render::textureVisible) {   
                        unsigned int u = static_cast<unsigned int>(std::clamp(texU * wInv * texWidth, 0.0f, static_cast<float>(texWidth-1)));
                        unsigned int v = static_cast<unsigned int>(std::clamp(texV * wInv * texHeight, 0.0f, static_cast<float>(texHeight-1)));

                        texCol = texture->getPixel({u, v});
                        pixels.append(sf::Vertex{sf::Vector2f(j, i), sf::Color(texCol.r * illumination, texCol.g * illumination, texCol.b * illumination)});
                    } else {
                        pixels.append(sf::Vertex{sf::Vector2f(j, i), sf::Color(triCol.r, triCol.g, triCol.b)});
                    }

                    depthBuffer(i * glbl::window::width + j) = texW;
                }
                
                t += tstep;
            }
        }
    }

    return pixels;
}

int Triangle::clipAgainsPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Triangle& inTri, Triangle& outTri1, Triangle& outTri2) {
    Vec3d normalizedPlaneNormal = planeNormal.normalize();

    auto dist = [&](const Vec3d& point) {
        return normalizedPlaneNormal.dot(point) - normalizedPlaneNormal.dot(planePoint);
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

        outTri1.p[1].intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[0], t);
        outTri1.t[1].intersectPlane(*insideTex[0], *outsideTex[0], t);

        outTri1.p[2].intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[1], t);
        outTri1.t[2].intersectPlane(*insideTex[0], *outsideTex[1], t);

        return 1;
    }

    if (insidePointCount == 2 && outsidePointCount == 1) {
        float t;

        outTri1 = inTri;
        
        outTri1.p[0] = *insidePoints[0];
        outTri1.t[0] = *insideTex[0];

        outTri1.p[1] = *insidePoints[1];
        outTri1.t[1] = *insideTex[1];

        outTri1.p[2].intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[0], t);
        outTri1.t[2].intersectPlane(*insideTex[0], *outsideTex[0], t);

        outTri2 = inTri;

        outTri2.p[0] = *insidePoints[1];
        outTri2.t[0] = *insideTex[1];

        outTri2.p[1] = outTri1.p[2];
        outTri2.t[1] = outTri1.t[2];

        outTri2.p[2].intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[1], *outsidePoints[0], t);
        outTri2.t[2].intersectPlane(*insideTex[1], *outsideTex[0], t);

        return 2;
    }

    return true;
}