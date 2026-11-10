// 70649F Golden Hand Maidens
#include "vex.h"
#include "vector2.h"
#include "behavior.h"
#include "devices.h"
#include "odom.h"
#include "movement.h"
#include "input.h"

using namespace vex;
using namespace behavior;
using namespace devices;

competition comp;

void pre_auton() {
  odom::recalibrate_x(0, 0);
  odom::recalibrate_y(0, 0);
  odom::initialize_odom();
  set_mode(DRIVER_CONTROL);
}

void autonomous(void) {
}

void usercontrol(void) {
  while (1) {
    switch (active_mode)
    {
      case (MATCH_LOAD): matchload::process(); break;
      case (DRIVER_CONTROL): input::process_axes(); break;
      default: break;
    }
    input::process_buttons();
    wait(input::processms, msec);
    odom::update_odom();
    odom::calculate_confidence();
  }
}
int main() {
  comp.autonomous(autonomous);
  comp.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(20, msec);
  }
}