#include "movement.h"

using namespace devices;

#ifndef clamp
float clamp(float value, float min, float max) {
  return fmax(min, fmin(max, value));
}
#endif
bool movement::moveTo(vector2 target) {
  vector2 displacement = polar::toPolar(target - odom::position);
  float angleError = polar::normalize_angle(displacement.y - odom::heading);

  if ( displacement.x < moveAccThreshold / odom::confidence.x ) {
    return false;
  }
  const float kP_linear = 2;
  const float kP_angular = 3;

  float linearVelocity = displacement.x * kP_linear;
  float angularVelocity = angleError * kP_angular;

  // reduce forward velocity when not facing target
  linearVelocity *= fmax(0.0, cos(angleError));

  // differential drive movement
  float leftVel = linearVelocity - angularVelocity * trackWidth / 2.0;
  float rightVel = linearVelocity + angularVelocity * trackWidth / 2.0;

  // convert vel to motor percent
  const float maxPodSpeed = 165.0;

  int leftPercent = (int)clamp(
      (leftVel / maxPodSpeed) * 100.0,
      -100, 100
  );

  int rightPercent = (int)clamp(
      (rightVel / maxPodSpeed) * 100.0,
      -100, 100
  );
  leftPod.setVelocity(leftPercent, percent);
  rightPod.setVelocity(rightPercent, percent);

  leftPod.spin(forward);
  rightPod.spin(forward);

  return true;
}

// rotates to the bot to a specified angle. returns whether it spun the motors to rotate
bool movement::rotateTo(double target) {
  float angleError = polar::normalize_angle(target - odom::heading);;
  // if angle is within pi/36 (5 deg)
  if (angleError < rotAccThreshold / odom::confidence.y) {
    return false;
  }
  const float kP_angular = 3;

  // calculate velocities
  float angularVelocity = angleError * kP_angular;
  double leftVel = -angularVelocity * trackWidth / 2.0;
  double rightVel = angularVelocity * trackWidth / 2.0;

  // convert vel to percent
  const float maxPodSpeed = 360.0;
  int leftPercent = (int)clamp(
      (leftVel / maxPodSpeed) * 100.0,
      -100, 100
  );
  int rightPercent = (int)clamp(
      (rightVel / maxPodSpeed) * 100.0,
      -100, 100
  );

  leftPod.setVelocity(leftPercent, percent);
  rightPod.setVelocity(rightPercent, percent);

  leftPod.spin(forward);
  rightPod.spin(forward);

  return true;
}