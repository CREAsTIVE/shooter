//
// Created by Иван Ильин on 13.01.2021.
//

#include "Triangle.h"

Triangle::Triangle () {
    p[0] = Point4D{0,0,0,1};
    p[1] = Point4D{0,0,0,1};
    p[2] = Point4D{0,0,0,1};
}

Triangle::Triangle(const Point4D& p1, const Point4D& p2, const Point4D& p3, double w) {
    p[0] = Point4D{p1.x(), p1.y(), p1.z(), w};
    p[1] = Point4D{p2.x(), p2.y(), p2.z(), w};
    p[2] = Point4D{p3.x(), p3.y(), p3.z(), w};
}

Triangle Triangle::operator*(const Matrix4x4 &matrix4X4) const {
    return Triangle(*this) *= matrix4X4;
}

Triangle &Triangle::operator*=(const Matrix4x4 &matrix4X4) {
    p[0] = matrix4X4 * p[0];
    p[1] = matrix4X4 * p[1];
    p[2] = matrix4X4 * p[2];

    return *this;
}

Point4D Triangle::norm() const {

    Point4D v1 = p[1] - p[0];
    Point4D v2 = p[2] - p[0];

    return v1.cross3D(v2).normalized();
}

Point4D Triangle::operator[](int i) const {
    return p[i];
}

Point4D &Triangle::operator[](int i) {
    return p[i];
}

Point4D Triangle::pos() const {
    return (p[0] + p[1] + p[2])/3.0;
}

Triangle::Triangle(const Triangle &triangle) {
    clip = triangle.clip;
    color = triangle.color;
    p[0] = triangle[0];
    p[1] = triangle[1];
    p[2] = triangle[2];
}

bool Triangle::isPointInside(const Point4D &point) const {
    Point4D triangleNorm = norm();

    double dot1 = (point - p[0]).cross3D(p[1] - p[0]).dot(triangleNorm);
    double dot2 = (point - p[1]).cross3D(p[2] - p[1]).dot(triangleNorm);
    double dot3 = (point - p[2]).cross3D(p[0] - p[2]).dot(triangleNorm);

    if((dot1 >= 0 && dot2 >= 0 && dot3 >= 0) || (dot1 <= 0 && dot2 <= 0 && dot3 <= 0))
        return true;
    return false;
}

Triangle &Triangle::operator=(const Triangle &triangle) {
    if(&triangle != this) {
        clip = triangle.clip;
        color = triangle.color;
        p[0] = triangle[0];
        p[1] = triangle[1];
        p[2] = triangle[2];
    }
    return *this;
}
