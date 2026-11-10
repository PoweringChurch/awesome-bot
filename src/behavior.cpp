#include "behavior.h"

using namespace behavior;
using namespace field_constants;

game_team behavior::team = RED;
control_mode behavior::active_mode = DRIVER_CONTROL;
bool matchload::awaiting_piece = false;

void matchload::process()
{
  if (awaiting_piece)
  {
    vector2 matchloaders[2];
    if (team == RED) {
      matchloaders[0] = redMatchloader1;
      matchloaders[1] = redMatchloader2;
    } else {
      matchloaders[0] = blueMatchloader1;
      matchloaders[1] = blueMatchloader2;
    }
    vector2 displace1 = polar::toPolar(odom::position - matchloaders[0]);
    vector2 displace2 = polar::toPolar(odom::position - matchloaders[1]);

    // if matchloader 1 is nearer than matchloader 2
    bool reorient = false;
    if (displace1.x < displace2.x) {
      reorient = !movement::moveTo(matchloaders[0]);
    } else {
      reorient = !movement::moveTo(matchloaders[1]);
    }
    if (reorient) {
      movement::rotateTo(0);
    }
  } else {
    vector2 goals[2];
    if (team == RED) {
      goals[0] = redGoal1;
      goals[1] = redGoal2;
    } else {
      goals[0] = blueGoal1;
      goals[1] = blueGoal2;
    }
    vector2 displace1 = polar::toPolar(odom::position - goals[0]);
    vector2 displace2 = polar::toPolar(odom::position - goals[1]);
    bool reorient = false;
    if (displace1.x < displace2.x) {
      reorient = !movement::moveTo(goals[0]);
    } else {
      reorient = !movement::moveTo(goals[1]);
    }
    if (reorient) {
      movement::rotateTo(0);
    }
  }
}
void behavior::set_mode(control_mode c) {
  active_mode = c;
}
void behavior::cycle_mode() {
    int new_mode = (int)active_mode + 1;
    set_mode((control_mode)(new_mode % 2));
    if (active_mode == MATCH_LOAD) {
        matchload::awaiting_piece = true;
    }
}