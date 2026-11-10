#ifndef DISPLAY_H
#define DISPLAY_H

#include "devices.h"
#include "behavior.h"
#include "input.h"
#include "odom.h"
#include <string>
namespace display {
    extern int current_screen;
    void draw_screen();
}
#endif