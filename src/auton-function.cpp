#include "auton-function.h"
#include "basic-functions.h"
#include "PID.h"
#include "calc.h"
#include "parameters.h"
#include "sensors.h"
using namespace vex;

static float arm_output;

/**
 * 实现机器人基座的软启动向前移动。
 * 软启动旨在平滑地从初始功率增加到最终功率，避免突然启动造成的冲击或损坏。
 *
 * @param _power_init 初始功率，范围应在0到1之间。
 * @param _power_final 最终功率，范围应在0到1之间。
 * @param _duration 移动持续的时间，单位为秒。
 */
void softStartTimerForward(float _power_init, float _power_final, int _duration)
{
    // 创建一个定时器对象，用于跟踪时间
    auto timer = MyTimer();
    // 计算每单位时间功率的变化量，用于平滑过渡
    float step = (_power_final - _power_init) / _duration;

    // 当时间未达到指定持续时间时，循环执行
    while (timer.getTime() < _duration)
    {
        // 根据当前时间计算并应用相应的功率
        moveBase(_power_init + timer.getTime() * step);
        // 为了让运动更平滑，每次迭代后暂停一小段时间
        this_thread::sleep_for(5);
    }

    // 达到指定持续时间后，停止基座的运动
    stopBase();
}

void timerForward(float _power, int _duration)
{
    moveBase(_power);
    this_thread::sleep_for(_duration);
    stopBase();
}

void posForwardRelLegacy(float _power, float _target)
{
    float start = getForwardPos();
    float power = sign(_target) * fabs(_power);
    moveBase(power);
    while (fabs(getForwardPos() - start) < fabs(_target))
    {
        this_thread::sleep_for(5);
    }
    stopBase();
}

/**
 * @brief 以相对目标位置前进
 *
 * 本函数控制机器人以指定功率相对当前位置向前或向后移动到目标位置。
 * 功能实现过程中，会实时调整机器人朝向，以确保移动过程中方向的准确性。
 *
 * @param _power 移动的动力大小，正数表示向前移动，负数表示向后移动。
 * @param _target 目标位置，正数表示向前移动，负数表示向后移动。
 */
void posForwardRel(float _power, float _target)
{
    // 获取起始位置，用于后续计算相对位移
    float start = getForwardPos();
    // 确定动力方向，确保即使输入为负数，也能正确前进或后退
    float power = sign(_target) * fabs(_power);
    // 获取初始朝向，用于后续调整机器人方向
    float prefer_heading = getHeading();
    // 用于记录朝向偏差
    float heading_error = 0;
    // 当当前位置相对起始位置的位移小于目标位移时，持续移动
    while (fabs(getForwardPos() - start) < fabs(_target))
    {
        // 计算当前朝向与初始朝向的偏差
        heading_error = prefer_heading - getHeading();
        // 确保方向偏差在合理范围内，避免过度调整导致的不稳定
        heading_error *= 1;
        heading_error = fabs(heading_error) > 10 ? 10 * sign(heading_error) : heading_error;
        moveBaseWithRotate(power, heading_error);
        this_thread::sleep_for(5);
    }
    stopBase();
}

/**
 * @brief 设置机器人向前的绝对位置
 *
 * 本函数通过计算目标位置与当前前进位置的相对距离，调用相对位置移动函数来实现机器人向前的绝对位置移动。
 * 主要用于在知道目标位置的情况下，直接指定机器人应该移动到的绝对位置。
 *
 * @param _power 移动的动力大小，影响移动速度和加速度。
 * @param _target 目标位置，以某个参考系下的绝对位置表示。
 */
void posForwardAbs(float _power, float _target)
{
    // 计算目标位置与当前位置的相对距离
    float target_rel = _target - getForwardPos();

    // 调用相对位置移动函数，以指定的动力和相对距离向前移动
    posForwardRel(_power, target_rel);
}
/**
 * 通过PID控制器将当前前进位置相对目标位置进行调整
 *
 * 本函数通过获取当前前进位置，并将目标位置相对于当前位置进行计算，然后传递给pidForwardAbs函数，
 * 由pidForwardAbs函数完成绝对位置控制。这种方式适用于已经知道当前位置，并希望以相对方式调整到目标位置的场景。
 *
 * @param _target 目标位置的相对值，即从当前位置到目标位置的距离。
 */
void pidForwardRel(float _target)
{
    pidForwardAbs(getForwardPos() + _target);
}
/**
 * 使用PID算法驱动机器人向前移动到目标位置。
 *
 * 本函数通过初始化和持续更新一个PID控制器，来控制机器人向前移动到指定的绝对位置。
 * PID控制器根据当前位置与目标位置的偏差进行计算，并输出一个控制量来调整机器人的速度。
 *
 * @param _target 机器人需要移动到的目标位置。
 */
void pidForwardAbs(float _target)
{
    auto pid = PID();
    pid.setCoefficient(BASE_FORWARD_PID[0], BASE_FORWARD_PID[1], BASE_FORWARD_PID[2]);
    pid.setTarget(_target);
    pid.setIMax(20);
    pid.setIRange(5);
    pid.setErrorTolerance(1); // 设定误差小于多少的时候可以跳出循环
    pid.setDTolerance(5);     // 设定速度小于多少的时候车可以跳出循环
    pid.setJumpTime(20);
    while (!pid.targetArrived())
    {
        pid.update(getForwardPos());
        moveBase(pid.getOutput());
        this_thread::sleep_for(5);
    }
    stopBase();
}

void softStartTimerRotate(float _power_init, float _power_final, int _duration)
{
    auto timer = MyTimer();
    float step = (_power_final - _power_init) / _duration;
    while (timer.getTime() < _duration)
    {
        rotateBase(_power_init + timer.getTime() * step);
        this_thread::sleep_for(5);
    }
    stopBase();
}

void timerRotate(float _power, int _duration)
{
    rotateBase(_power);
    this_thread::sleep_for(_duration);
    stopBase();
}

void angleRotateRel(float _power, float _target)
{
    angleRotateAbs(_power, getHeading() + _target);
}

void angleRotateAbs(float _power, float _target)
{
    while (fabs(_target - getHeading()) > 180)
    {
        if (_target - getHeading() > 0)
            _target -= 360;
        else
            _target += 360;
    }
    float start = getHeading();
    float power = sign(_target - getHeading()) * fabs(_power);
    float target = fabs(_target - getHeading());
    rotateBase(power);
    while (fabs(getHeading() - start) < target)
    {
        this_thread::sleep_for(5);
    }
    stopBase();
}

void pidRotateRel(float _target)
{
    pidRotateAbs(getHeading() + _target);
}
/**
 * @brief 使用PID算法实现绝对角度旋转
 *
 * 本函数通过PID算法控制基座旋转到指定的绝对角度。首先，它修正目标角度和当前角度的差值，以避免超过180度的旋转。
 * 然后，配置PID控制器的参数，并不断更新控制器，直到目标角度到达。
 *
 * @param _target 目标角度
 */
void pidRotateAbs(float _target)
{
    auto pid = PID();
    _target-=1.5;//玄学矫正
    // data transfer to prevend from huge angle rotation
    while (fabs(_target - getHeading()) > 180)
    {
        if (_target - getHeading() > 0)
            _target -= 360;
        else
            _target += 360;
    }
    pid.setTarget(_target);
    pid.setIMax(20);
    pid.setIRange(20); // use if sentance to define the I coeff
    pid.setErrorTolerance(1);
    pid.setDTolerance(2);
    pid.setJumpTime(20);
    while (!pid.targetArrived())
    {
        pid.setCoefficient(BASE_ROTATE_PID[0], BASE_ROTATE_PID[1], BASE_ROTATE_PID[2]);
        pid.update(getHeading());
        rotateBase(pid.getOutput());
        this_thread::sleep_for(5);
    }
    resetForwardPos();
    stopBase();
}

void setArmVolt(float _input)
{
    arm_output = _input;
}

void softStartRotateArm(float _power_final)
{
    if (fabs(arm_output - _power_final) > 5)
        arm_output += 10 * sign(_power_final - arm_output);
}

void angleRotateArmRel(float _power, float _target, bool _stop_flat)
{
    float start = Sensors::getInstance()->getArmRotation();
    float power = sign(_target) * fabs(_power);
    if (fabs(Sensors::getInstance()->getArmRotation() - start) < fabs(_target))
    {
        arm_output = power;
    }
    else if (_stop_flat)
    {
        arm_output = 0;
    }
}

void angleRotateArmAbs(float _power, float _target, bool _stop_flat)
{
    float target_rel = _target - Sensors::getInstance()->getArmRotation();
    angleRotateArmRel(_power, target_rel, _stop_flat);
}

void pidRotateArmRel(float _target)
{
    pidRotateArmAbs(Sensors::getInstance()->getArmRotation() + _target);
}

void pidRotateArmAbs(float _target)
{
    static auto pid = PID();
    // data transfer to prevend from huge angle rotation
    pid.setTarget(_target);
    pid.setIMax(20);
    pid.setIRange(20); // use if sentance to define the I coeff
    pid.setErrorTolerance(1);
    pid.setDTolerance(2);
    pid.setJumpTime(20);
    pid.setCoefficient(ARM_ROTATE_PID[0], ARM_ROTATE_PID[1], ARM_ROTATE_PID[2]);
    pid.update(Sensors::getInstance()->getArmRotation());
    arm_output = pid.getOutput();
}

void rotateArmAbs(float _max_power, float _target)
{
    float power = sign(_target - Sensors::getInstance()->getArmRotation()) * _max_power;
    if (fabs(_target - Sensors::getInstance()->getArmRotation()) > 40)
        softStartRotateArm(power);
    else
        pidRotateArmAbs(_target);
}

static ArmEvent arm_event;
static ArmState arm_state;

void setArmEvent(ArmEvent _input)
{
    arm_event = _input;
}

ArmState getArmState()
{
    return arm_state;
}

void autonArm()
{
    MyTimer timer;
    while (1)
    {
        switch (arm_event)
        {
        case ArmEvent::reposition:
            if (Sensors::getInstance()->getArmRotation() > 2)
                rotateArmAbs(40, 0);
            else
                setArmVolt(-5);
            if (Sensors::getInstance()->getArmRotation() < 2)
                arm_state = ArmState::init;
            break;
        case ArmEvent::take_item:
            if (Sensors::getInstance()->getArmRotation() > 8)
                arm_state = ArmState::ready;
            rotateArmAbs(50, 10);
            break;
        case ArmEvent::score_low:
            if (Sensors::getInstance()->getArmRotation() > 50)
                arm_state = ArmState::low;
            rotateArmAbs(80, 52);
            break;
        case ArmEvent::score_high:
            if (Sensors::getInstance()->getArmRotation() > 68)
                arm_state = ArmState::high;
            rotateArmAbs(80, 70);
            break;
        case ArmEvent::reset_encoder:
            if (arm_state == ArmState::init)
                setArmVolt(-20);
            Sensors::getInstance()->resetArmRotation();
            break;
        case ArmEvent::turn_on_handle_mode:
            arm_state = ArmState::handle_mode;
            break;
        }
        spinArm(arm_output);
        this_thread::sleep_for(5);
    }
}