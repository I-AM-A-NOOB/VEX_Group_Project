
#ifndef PARAMETERS_H_
#define PARAMETERS_H_

#include "vex.h"

#define MOVEMENT_LOWER_LIMIT 5
#define JOYSTICK_DEADZONE 5
#define ADS 0.4
#define CHASSIS_GEAR_RATIO 1
#define WHEEL_DIAMETER 82.55 // units = mm
#define WHEEL_RADIUS 41.275  // units = mm
#define BASE_RADIUS 143.8    // units = mm
#define IMU_HEADING_5 1779   // units = deg

#define SENSORS_REFRESH_TIME 5
#define POSITION_REFRESH_TIME 5

#define WHEEL_NUM 3
const double WHEEL_DIRECTION[3] = {
    M_PI * 2 / 3, // RIGHT
    M_PI * 4 / 3, // LEFT
    M_PI * 6 / 3, // BACK
};

const float BASE_FORWARD_PID[3] = {2, 0, 0};
const float BASE_ROTATE_PID[3] = {0.8, 0.05, 0.1}; //[P,I,D] P:速度，会导致振荡；D:刹车
const float ARM_ROTATE_PID[3] = {2, 0.1, 0};

#endif