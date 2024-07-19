#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_
#include "vex.h"
using  namespace vex;

extern brain Brain;
extern controller Controller1;
// actuator
extern motor Base[3];
extern motor Roller;
extern motor Arm;
// sensor
extern inertial Imu;
extern line Lntrck[3];
#endif