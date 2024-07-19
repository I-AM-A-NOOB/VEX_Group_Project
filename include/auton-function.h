#ifndef AUTON_FUNCTION_H_
#define AUTON_FUNCTION_H_

void softStartTimerForward(float _power_init, float _power_final, int _duration);
void timerForward(float _power, int _duration);
void posForwardRel(float _power, float _target);
void posForwardAbs(float _power, float _target);
void pidForwardRel(float _target);
void pidForwardAbs(float _target);

void softStartTimerRotate(float _power_init, float _power_final, int _duration);
void timerRotate(float _power, int _duration);
void angleRotateRel(float _power, float _target);
void angleRotateAbs(float _power, float _target);
void pidRotateRel(float _target);
void pidRotateAbs(float _target);

void setArmVolt(float _input);

void softStartRotateArm(float _power_final);
void angleRotateArmRel(float _power, float _target, bool _stop_flat = 0);
void angleRotateArmAbs(float _power, float _target, bool _stop_flat = 0);
void pidRotateArmRel(float _target);
void pidRotateArmAbs(float _target);
void rotateArmAbs(float _max_power, float _target);

enum ArmState {
    init,
    ready,
    low,
    high,
    handle_mode
};

enum ArmEvent {
    reposition,
    take_item,
    score_low,
    score_high,
    reset_encoder,
    turn_on_handle_mode
};

void setArmEvent(ArmEvent _input);
ArmState getArmState();

void autonArm();
#endif