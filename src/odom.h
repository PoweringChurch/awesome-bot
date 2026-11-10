#ifndef ODOM_H
#define ODOM_H
#include "devices.h"
#include "vector2.h"
#include "polar.h"
#include "math.h"
#include "behavior.h"

namespace odom {
    extern polar delta;
    extern vector2 position;
    extern vector2 confidence;
    extern double heading;

    extern double prev_left;
    extern double prev_right;
    
    void recalibrate_x(double position, double facing);
    void recalibrate_y(double position, double facing);

    void initialize_odom();
    void update_odom();
    void calculate_confidence();
}
#endif