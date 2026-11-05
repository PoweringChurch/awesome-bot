#include "vex.h"
#include "vector2.h"

using namespace vex;

competition comp;

drivetrain drive;
motor_group rightPod;
motor_group leftPod;

vector2 startPosition;

vector2 polar_delta;
vector2 position;
double heading;

bool automatic = false;

// how much distance is travelled in one spin of the wheels
const double wheelTravel = 260; // ie circumference of wheels (3.25in diameter)
const double trackWidth = 380; // distance between left and right wheels
const double wheelBase = 216; // diatance between front and back wheels
const double ratio = 0.6; // 36t : 60t gears

drivetrain setup_drive()
{
  // grey wheels
  motor rightWheel1 = motor(PORT1, ratio6_1, false);
  motor rightWheel2 = motor(PORT2, ratio6_1, false);
  motor rightWheel3 = motor(PORT3, ratio6_1, false);
  // green wheels
  motor leftWheel1 = motor(PORT4, ratio6_1, false);
  motor leftWheel2 = motor(PORT5, ratio6_1, false);
  motor leftWheel3 = motor(PORT6, ratio6_1, false);
  // pods
  rightPod = motor_group(rightWheel1, rightWheel2, rightWheel3);
  leftPod = motor_group(leftWheel1, leftWheel2, leftWheel3);

  drive = drivetrain(leftPod, rightPod, wheelTravel, trackWidth, wheelBase, mm, ratio);

  drive.setDriveVelocity(100, percent);
}

void pre_auton(void) {
  polar_delta = vector2(0,0);
};

void autonomous(void) {
}

bool stopTrainLeft = true;
bool stopTrainRight = true;

const int processms = 20;
const int deadband = 5;

void process_input(controller control)
{
  int trainLeftSpeed = control.Axis3.position() - control.Axis1.position();
  int trainRightSpeed = control.Axis3.position() + control.Axis1.position();

  if (trainLeftSpeed < deadband && trainLeftSpeed > -deadband) {
    if (stopTrainLeft)
    {
      leftPod.stop();
      stopTrainLeft = false;
    } else {
      stopTrainLeft = true;
    }
  }
  if (trainRightSpeed < deadband && trainRightSpeed > -deadband) {
    if (stopTrainRight) {
      rightPod.stop();
      stopTrainRight = false;
    } else {
      stopTrainRight = true;
    }
  }
  if (stopTrainLeft) {
    leftPod.setVelocity(trainLeftSpeed, percent);
    leftPod.spin(forward);
  }
  if (stopTrainRight) {
    rightPod.setVelocity(trainRightSpeed, percent);
    rightPod.spin(forward);
  }
}

double previousLeft = 1;
double previousRight = 1;

void update_odom() {
  float left = leftPod.position(rev);
  float right = rightPod.position(rev);

  double dL = (left - previousLeft) * wheelTravel * ratio;
  double dR = (right - previousRight) * wheelTravel * ratio;

  previousLeft = left;
  previousRight = right;
  double magnitude = (dL + dR) / 2.0;
  double theta = (dR - dL) / trackWidth;
  polar_delta.x = magnitude;
  polar_delta.y = theta;

  position.x += magnitude * cos(heading + (theta / 2.0));
  position.y += magnitude * sin(heading + (theta / 2.0));
  heading += theta;
}

vector2 toPolar(vector2 cartesian) {
  return vector2(sqrt(cartesian.x*cartesian.x + cartesian.y*cartesian.y), atan2(cartesian.y, cartesian.x));
}

float clamp(float value, float min, float max) {
    return fmax(min, fmin(max, value));
}

void moveTo(vector2 target) {
  vector2 displacement = toPolar(target - position);

  float angleError = displacement.y - heading;
  // normalize
  angleError = fmod(angleError + M_PI, 2.0f * M_PI);
  if (angleError < 0)
      angleError += 2.0f * M_PI;
  angleError -= M_PI;

  const float kP_linear = 2;
  const float kP_angular = 3;

  float linearVelocity = displacement.x * kP_linear;
  float angularVelocity = angleError * kP_angular;

  // reduce forward velocity when not facing target
  linearVelocity *= fmax(0.0, cos(angleError));

  // differential drive movement
  float leftVelocity = linearVelocity - angularVelocity * trackWidth / 2.0;
  float rightVelocity = linearVelocity + angularVelocity * trackWidth / 2.0;

  // convert vel to motor percent
  const float maxPodSpeed = 100.0;

  int leftPercent = (int)clamp(
      leftVelocity / maxPodSpeed * 100.0,
      -100, 100
  );

  int rightPercent = (int)clamp(
      rightVelocity / maxPodSpeed * 100.0,
      -100, 100
  );
  leftPod.setVelocity(leftPercent, percent);
  rightPod.setVelocity(rightPercent, percent);
}
void process_auto()
{
  
}
void usercontrol(void) {
  controller control = controller(primary);
  while (1) {
    if (automatic)
    {
      process_auto();
    } else {
      process_input(control);
    }
    wait(processms, msec);
    update_odom();
  }
}

int main() {
  setup_drive();
  comp.autonomous(autonomous);
  comp.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
