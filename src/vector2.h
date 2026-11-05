#ifndef VECTOR2_H
#define VECTOR2_H

struct vector2 {
public:
    vector2(float x, float y) {
        this->x = x;
        this->y = y;
    };
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