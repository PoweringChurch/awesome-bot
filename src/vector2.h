#ifndef VECTOR2_H
#define VECTOR2_H

struct vector2 {
public:
    vector2() {};
    vector2(double x, double y) : x(x), y(y) {}
    double x, y;
    vector2 operator+(const vector2& other) const {
        return vector2(x + other.x, y + other.y);
    }
    vector2 operator-(const vector2& other) const {
        return vector2(x - other.x, y - other.y);
    }
    vector2& operator+=(const vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    vector2& operator-=(const vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};
#endif