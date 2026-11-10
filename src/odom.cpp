#include "odom.h"

using namespace devices;

namespace odom {
  polar delta = polar(0,0);
  vector2 position = vector2(0,0);
  vector2 confidence = vector2(0,0);
  double heading = 0;

  double prev_left = 1;
  double prev_right = 1;
}

void odom::initialize_odom() {
    prev_left =
        (leftWheel1.position(rev) +
         leftWheel2.position(rev) +
         leftWheel3.position(rev)) / 3.0;

    prev_right =
        (rightWheel1.position(rev) +
         rightWheel2.position(rev) +
         rightWheel3.position(rev)) / 3.0;

    delta = polar(0, 0);
}

void odom::recalibrate_x(double x, double h) {
  position.x = x;
  confidence.x = 1;
  heading = polar::normalize_angle(h);
  initialize_odom();
}
void odom::recalibrate_y(double y, double h) {
  position.y = y;
  confidence.y = 1;
  heading = polar::normalize_angle(h);
  initialize_odom();
}
void odom::update_odom() {
  float left = (leftWheel1.position(rev)+leftWheel2.position(rev)+leftWheel3.position(rev)) / 3;
  float right = (rightWheel1.position(rev)+rightWheel2.position(rev)+rightWheel3.position(rev)) / 3;
  
  double dL = (left - prev_left) * wheelTravel * gearRatio;
  double dR = (right - prev_right) * wheelTravel * gearRatio;
  prev_left = left;
  prev_right = right;
  double magnitude = (dL + dR) / 2.0;
  double theta = (dR - dL) / trackWidth;
  delta.r = magnitude;
  delta.theta = theta;

  position.x += magnitude * cos(heading + (theta / 2.0));
  position.y += magnitude * sin(heading + (theta / 2.0));
  position.x = clamp(position.x, 0, behavior::field_constants::fieldSize.x);
  position.y = clamp(position.y, 0, behavior::field_constants::fieldSize.y);
  heading = polar::normalize_angle(heading + theta);
}
#ifndef clamp
double clamp(const double& value, const double& min, const double& max) {
  return fmax(min, fmin(max, value));
};
#endif
void odom::calculate_confidence() {
    float left_v1 = leftWheel1.velocity(percent);
    float left_v2 = leftWheel2.velocity(percent);
    float left_v3 = leftWheel3.velocity(percent);
    
    float right_v1 = rightWheel1.velocity(percent);
    float right_v2 = rightWheel2.velocity(percent);
    float right_v3 = rightWheel3.velocity(percent);

    float left_variance = (fabs(left_v1 - left_v2) + fabs(left_v2 - left_v3) + fabs(left_v1 - left_v3)) / 3.0;
    float right_variance = (fabs(right_v1 - right_v2) + fabs(right_v2 - right_v3) + fabs(right_v1 - right_v3)) / 3.0;

    float avg_torque = (leftWheel1.torque(Nm) + rightWheel1.torque(Nm)) / 2.0;
    float avg_velocity = (left_v1 + right_v1) / 2.0;
    
    bool is_stalled = (avg_torque > 1.05 && fabs(avg_velocity) < 5.0);

    double variance_penalty = clamp((left_variance + right_variance) / 30.0, 0.0, 0.8);
    double stall_penalty = is_stalled ? 0.7 : 0.0;
    double long_travel_penalty = delta.r / 1000;
    double lat_travel_penalty = delta.r / 800;
    confidence.x = clamp(1.0 - variance_penalty - stall_penalty - long_travel_penalty, 0.1, 1.0);
    confidence.y = clamp(confidence.y - lat_travel_penalty, 0.05, 1);
}
