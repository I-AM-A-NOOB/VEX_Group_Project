#include "sensors.h"

void Sensors::updateSens() {
    for(int i = 0; i < 3; ++i) {
        base_pos[i] = deg2rad(Base[i].position(degrees)) * WHEEL_RADIUS;
    }
    arm_piston_state = Arm.value();
    base_heading = 360-Imu.heading();
    base_rotation = Imu.rotation();
    for(int i = 0; i < 3; ++i) {
        line_ref[i] = Lntrck[i].reflectivity();
    }
    arm_rotation = Arm.position(degrees) / 5;
}

bool Sensors::getArmState() {
    return arm_piston_state;
}

float Sensors::getBaseRightPos() {
    return base_pos[0];
}

float Sensors::getBaseLeftPos() {
    return base_pos[1];
}

float Sensors::getBaseBackPos() {
    return base_pos[2];
}

float Sensors::getBasePos(int _num) {
    return base_pos[_num];
}

void Sensors::resetBaseRightPos() {
    Base[0].resetPosition();
}

void Sensors::resetBaseLeftPos() {
    Base[1].resetPosition();
}

void Sensors::resetBaseBackPos() {
    Base[2].resetPosition();
}

void Sensors::resetBasePos(int _num) {
    Base[_num].resetPosition();
}

void Sensors::resetBasePos() {
    resetBaseLeftPos();
    resetBaseRightPos();
    resetBaseBackPos();
}

float Sensors::getBaseHeading() {
    return base_heading;
}

void Sensors::setBaseHeading(float _heading) {
    Imu.setHeading(360-_heading, degrees);
}

void Sensors::resetBaseHeading() {
    Imu.resetHeading();
}

float Sensors::getBaseRotation() {
    return base_rotation;
}

int Sensors::getLineRightRef() {
    return line_ref[0];
}

int Sensors::getLineMiddleRef() {
    return line_ref[1];
}

int Sensors::getLineLeftRef() {
    return line_ref[2];
}

float Sensors::getArmRotation() {
  return arm_rotation;
}

void Sensors::resetArmRotation() {
  Arm.resetPosition();
}

void updateSensors() {
    while(1) {
        Sensors::getInstance()->updateSens();
        this_thread::sleep_for(SENSORS_REFRESH_TIME);
    }
}
