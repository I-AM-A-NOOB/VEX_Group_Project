#ifndef BASIC_FUNCTIONS_H_
#define BASIC_FUNCTIONS_H_

void spinRightMotor(float);
void spinLefttMotor(float);
void spinBackMotor(float);

void stopRightMotor();
void stopLefttMotor();
void stopBackMotor();

void setBaseVelHeading(float);
void setGlobalVelHeading(float);

float getCoeff(int _num);
float getRightCoeff();
float getLeftCoeff();
float getBackCoeff();

void moveBase(float);
void rotateBase(float);
void moveBaseWithRotate(float _move_power, float _rotate_power);
void stopBase();

float getForwardPos();
void resetForwardPos();
float getHeading();

void spinRoller(float);
void spinArm(float);

#endif