#include "robot-config.h"

// 定义设备对象

brain Brain;
controller Controller1(primary);
// actuator
motor Base[3] = {
    // 0 = right, 1 = left, 2 = back
    motor(PORT2, ratio18_1, true),
    motor(PORT3, ratio18_1, true),
    motor(PORT1, ratio18_1, true)
};
motor Roller = motor(PORT12, ratio18_1, false);
motor Arm = motor(PORT11, ratio18_1, true);
// sensor
inertial Imu = inertial(PORT9);
line Lntrck[3] = {
    line(Brain.ThreeWirePort.B), 
    line(Brain.ThreeWirePort.C), 
    line(Brain.ThreeWirePort.D) 
};