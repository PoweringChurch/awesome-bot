#ifndef POLAR_H
#define POLAR_H
#include "vector2.h"
#include "math.h"
// serves as an explicit alias for a vector2 with additional functions for polar coordinate calculations
struct polar {
public:
    double r, theta;
    polar() {};
    polar(double r, double theta) : r(r), theta(theta) {}

    static vector2 toPolar(const vector2& cartesian) {
        return vector2(sqrt(cartesian.x*cartesian.x + cartesian.y*cartesian.y), atan2(cartesian.y, cartesian.x));
    }
    static double normalize_angle(const double& angle) {
        double alpha = fmod(angle + M_PI, 2.0f * M_PI);
        if (alpha < 0)
            alpha += 2.0f * M_PI;
        alpha -= M_PI;
        return alpha;
    }
};
#endif