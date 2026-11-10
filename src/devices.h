#ifndef DEVICES_H
#define DEVICES_H

#include "vex.h"
using namespace vex;

namespace devices {
    extern brain mainBrain;
    extern controller control;

    extern motor rightWheel1;
    extern motor rightWheel2;
    extern motor rightWheel3;
    extern motor leftWheel1;
    extern motor leftWheel2;
    extern motor leftWheel3;

    extern motor_group rightPod;
    extern motor_group leftPod;

    // how much distance is travelled in one spin of the wheels
    const double wheelTravel = 260;
    // distance between left and right wheels
    const double trackWidth = 380;
    // distance between front and back wheels
    const double wheelBase = 216;
    // 36t : 60t gears
    const double gearRatio = 0.6;
}
#endif