#include "math/Triangle.hpp"

Triangle::Triangle() : p{ Vec3d(), Vec3d(), Vec3d() } {}
Triangle::Triangle(Vec3d p1, Vec3d p2, Vec3d p3) : p{ p1, p2, p3 } {}

void Triangle::translateX(float f) { for (auto& v : p) { v.x += f; } }
void Triangle::translateY(float f) { for (auto& v : p) { v.y += f; } }
void Triangle::translateZ(float f) { for (auto& v : p) { v.z += f; } }

void Triangle::scaleX(float f) { for (auto& v : p) { v.x *= f; } }
void Triangle::scaleY(float f) { for (auto& v : p) { v.y *= f; } }
void Triangle::scaleZ(float f) { for (auto& v : p) { v.z *= f; } }

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
    *this = *this * m;
    return *this;
}

Triangle operator*(const Triangle& t, const Mat4x4& m) {
    Triangle result;
    result.p[0] = t.p[0] * m;
    result.p[1] = t.p[1] * m;
    result.p[2] = t.p[2] * m;
    return result;
}

Vec3d Triangle::intersectPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Vec3d& lineStart, const Vec3d& lineEnd) {
    Vec3d normalizedPlaneNormal = planeNormal.normalize();
    float plane_d = -normalizedPlaneNormal.dotProd(planePoint);

    float ad = lineStart.dotProd(normalizedPlaneNormal);
    float bd = lineEnd.dotProd(normalizedPlaneNormal);

    float t = (-plane_d - ad) / (bd - ad);

    Vec3d lineStartToEnd = lineEnd - lineStart;
    Vec3d lineToIntersect = lineStartToEnd * t;
    return lineStart + lineToIntersect;
}

int Triangle::clipAgainsPlane(const Vec3d& planePoint, const Vec3d& planeNormal, const Triangle& inTri, Triangle& outTri1, Triangle& outTri2) {
    Vec3d normalizedPlaneNormal = planeNormal.normalize();

    auto dist = [&](const Vec3d& point) {
        return normalizedPlaneNormal.dotProd(point) - normalizedPlaneNormal.dotProd(planePoint);
    };

    const Vec3d* insidePoints[3];  
    const Vec3d* outsidePoints[3];
    int insideCount = 0, outsideCount = 0;

    float d0 = dist(inTri.p[0]);
    float d1 = dist(inTri.p[1]);
    float d2 = dist(inTri.p[2]);

    if (d0 >= 0) insidePoints[insideCount++] = &inTri.p[0]; else outsidePoints[outsideCount++] = &inTri.p[0];
    if (d1 >= 0) insidePoints[insideCount++] = &inTri.p[1]; else outsidePoints[outsideCount++] = &inTri.p[1];
    if (d2 >= 0) insidePoints[insideCount++] = &inTri.p[2]; else outsidePoints[outsideCount++] = &inTri.p[2];

    if (insideCount == 0) {
        return 0;
    }

    if (insideCount == 3) {
        outTri1 = inTri;
        return 1;
    }

    if (insideCount == 1 && outsideCount == 2) {
        outTri1 = inTri;
        outTri1.p[0] = *insidePoints[0];
        outTri1.p[1] = Triangle::intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[0]);
        outTri1.p[2] = Triangle::intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[1]);
        return 1;
    }

    if (insideCount == 2 && outsideCount == 1) {
        outTri1 = inTri;
        outTri2 = inTri;

        outTri1.p[0] = *insidePoints[0];
        outTri1.p[1] = *insidePoints[1];
        outTri1.p[2] = Triangle::intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[0], *outsidePoints[0]);

        outTri2.p[0] = *insidePoints[1];
        outTri2.p[1] = outTri1.p[2];
        outTri2.p[2] = Triangle::intersectPlane(planePoint, normalizedPlaneNormal, *insidePoints[1], *outsidePoints[0]);

        return 2;
    }

    return 0;
}