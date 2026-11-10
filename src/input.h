#ifndef INPUT_H
#define INPUT_H

#include "devices.h"
#include "behavior.h"
#include "display.h"

namespace input {
    const int processms = 20;
    const int deadband = 5;

    extern bool awaiting_recal_input;
    void process_buttons();
    void process_axes();
}
#endif