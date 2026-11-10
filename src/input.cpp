#include "input.h"

using namespace devices;

bool input::awaiting_recal_input = false;

bool stop_train_left = true;
bool stop_train_right = true;

void input::process_buttons()
{
    if (awaiting_recal_input) {
        double half_base = wheelBase / 2;
        if (control.ButtonRight.PRESSED) {
            odom::recalibrate_x(behavior::field_constants::fieldSize.x - half_base, 0);
        } else if (control.ButtonUp.PRESSED) {
            odom::recalibrate_y(half_base, M_PI_2);
        } else if (control.ButtonLeft.PRESSED) {
            odom::recalibrate_x(half_base, M_PI);
        } else if (control.ButtonDown.PRESSED) {
            odom::recalibrate_y(behavior::field_constants::fieldSize.y - half_base, M_3PI_4);
        } 
    }
    if (control.ButtonA.PRESSED) { 
        behavior::cycle_mode(); 
    }
    if (control.ButtonX.PRESSED) {
        if (behavior::active_mode == behavior::MATCH_LOAD) {
            behavior::matchload::awaiting_piece = !behavior::matchload::awaiting_piece;
        }
    }
    if (control.ButtonLeft.PRESSED) {
        int screenZeroIdx = display::current_screen - 1;
        display::current_screen = (screenZeroIdx - 1) % 2;
    }
    if (control.ButtonRight.PRESSED) {
        int screenZeroIdx = display::current_screen - 1;
        display::current_screen = (screenZeroIdx + 1) % 2;
    }
    if (control.ButtonY.PRESSED) {
        awaiting_recal_input = true;
    }
}
void input::process_axes() {
    int trainLeftSpeed = control.Axis3.position() - control.Axis1.position();
    int trainRightSpeed = -control.Axis3.position() - control.Axis1.position();
    if (trainLeftSpeed < deadband && trainLeftSpeed > -deadband) {
        if (stop_train_left)
        {
        leftPod.stop();
        stop_train_left = false;
        } else {
        stop_train_left = true;
        }
    }
    if (trainRightSpeed < deadband && trainRightSpeed > -deadband) {
        if (stop_train_right) {
        rightPod.stop();
        stop_train_right = false;
        } else {
        stop_train_right = true;
        }
    }

    leftPod.setVelocity(trainLeftSpeed, percent);
    leftPod.spin(forward);
    rightPod.setVelocity(trainRightSpeed, percent);
    rightPod.spin(forward);
}