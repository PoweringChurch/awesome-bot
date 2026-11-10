#ifndef BOT_H
#define BOT_H

#include "devices.h"
#include "odom.h"
#include "vector2.h"
#include "polar.h"

namespace movement {
    // how close to be before calling it good enough for a position with moveto, measured in millimeters
    const double moveAccThreshold = 100;
    // how close to be before calling it good enough for a rotation with rotateto, measured in radians
    const double rotAccThreshold = 0.17;

    // moves the bot towards a specified point. returns whether it spun the motors to move
    bool moveTo(vector2 target);
    // rotates the bot towards a specified angle. returns whether it spun the motors to move
    bool rotateTo(double target);
}

#endif