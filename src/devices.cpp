#include "devices.h"

namespace devices {
    brain mainBrain = brain();
    controller control = controller(primary);
    
    motor rightWheel1 = motor(PORT1, ratio6_1, false);
    motor rightWheel2 = motor(PORT2, ratio6_1, false);
    motor rightWheel3 = motor(PORT3, ratio6_1, false);

    motor leftWheel1 = motor(PORT4, ratio6_1, false);
    motor leftWheel2 = motor(PORT5, ratio6_1, false);
    motor leftWheel3 = motor(PORT6, ratio6_1, false);

    motor_group rightPod = motor_group(rightWheel1, rightWheel2, rightWheel3);
    motor_group leftPod = motor_group(leftWheel1, leftWheel2, leftWheel3);
}