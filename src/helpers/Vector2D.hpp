#pragma once

#include <math.h>

class Vector2D {
   public:
    Vector2D(double, double);
    Vector2D();
    ~Vector2D();

    double x = 0;
    double y = 0;

    // returns the scale
    double normalize();

    Vector2D operator+(const Vector2D a) const {
        return Vector2D(this->x + a.x, this->y + a.y);
    }
    Vector2D operator-(const Vector2D a) const {
        return Vector2D(this->x - a.x, this->y - a.y);
    }
    Vector2D operator*(const float a) const {
        return Vector2D(this->x * a, this->y * a);
    }
    Vector2D operator/(const float a) const {
        return Vector2D(this->x / a, this->y / a);
    }
    Vector2D& operator/=(const float a) {
        x /= a;
        y /= a;
        return *this;
    }

    bool operator==(const Vector2D& a) const {
        return a.x == x && a.y == y;
    }

    bool operator!=(const Vector2D& a) const {
        return a.x != x || a.y != y;
    }

    Vector2D floor();

    friend Vector2D operator/(Vector2D lhs, const Vector2D& rhs) {
        return Vector2D(lhs.x / rhs.x, lhs.y / rhs.y);
    }

    friend Vector2D operator*(Vector2D lhs, const Vector2D& rhs) {
        return Vector2D(lhs.x * rhs.x, lhs.y * rhs.y);
    }
    
    friend Vector2D operator*(const float scalar, const Vector2D& vec) {
        return Vector2D(vec.x * scalar, vec.y * scalar);
    }
    
    friend Vector2D operator*(Vector2D& vec, const float scalar) {
        return Vector2D(vec.x * scalar, vec.y * scalar);
    }
};
