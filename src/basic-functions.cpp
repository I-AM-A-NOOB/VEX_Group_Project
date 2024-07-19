#include "basic-functions.h"
#include "calc.h"
#include "robot-config.h"
#include "sensors.h"

static float base_vel_heading;

/**
 * @brief 右电机驱动
 * @param _input 从-100到100，对电机进行PWM控制
 */
void spinRightMotor(float _input)
{
    Base[0].spin(fwd, _input * 127, voltageUnits::mV);
}

/**
 * @brief 左电机驱动
 * @param _input 从-100到100，对电机进行PWM控制
 */
void spinLefttMotor(float _input)
{
    Base[1].spin(fwd, _input * 127, voltageUnits::mV);
}

/**
 * @brief 后电机驱动
 * @param _input 从-100到100，对电机进行PWM控制
 */
void spinBackMotor(float _input)
{
    Base[2].spin(fwd, _input * 127, voltageUnits::mV);
}

/**
 * @brief 停止右电机
 */
void stopRightMotor()
{
    Base[0].stop(coast);
}

/**
 * @brief 停止左电机
 */
void stopLefttMotor()
{
    Base[1].stop(coast);
}

/**
 * @brief 停止后电机
 */
void stopBackMotor()
{
    Base[2].stop(coast);
}

/**
 * @brief 在机器人坐标系设定底盘平移方向
 * @param _heading 单位：rad弧度，从0到2pi
 */
void setBaseVelHeading(float _heading)
{
    base_vel_heading = _heading;
}
/**
 * @brief 在世界坐标系设定底盘平移方向
 * @param _heading 单位：rad弧度，从0到2pi
 */
void setGlobalVelHeading(float _heading)
{
    base_vel_heading = _heading - deg2rad(Sensors::getInstance()->getBaseHeading());
}

float getCoeff(int _num)
{
    return cos(base_vel_heading - M_PI / 3 * 2 * (_num + 1));
}

/**
 * @brief 获取右轮速度系数
 */
float getRightCoeff()
{
    return cos(base_vel_heading - M_PI / 3 * 2);
}

/**
 * @brief 获取左轮速度系数
 */
float getLeftCoeff()
{
    return cos(base_vel_heading - M_PI / 3 * 4);
}

/**
 * @brief 获取后轮速度系数
 */
float getBackCoeff()
{
    return cos(base_vel_heading - M_PI / 3 * 6);
}

/**
 * @brief 平移机器人底盘（需要先设定平移速度方向）
 * @param _power 电机PWM调速，从0到100
 */
void moveBase(float _power)
{
    spinRightMotor(_power * getRightCoeff());
    spinLefttMotor(_power * getLeftCoeff());
    spinBackMotor(_power * getBackCoeff());
}

/**
 * @brief 旋转机器人底盘
 * @param _power 电机PWM调速，从-100到100
 */
void rotateBase(float _power)
{
    spinRightMotor(-0.75 * _power);
    spinLefttMotor(-0.75 * _power);
    spinBackMotor(-0.75 * _power);
}

/**
 * @brief 机器人底盘做平面运动（需要先设定平移速度方向）
 * @param _power 电机PWM调速，从-100到100
 */
void moveBaseWithRotate(float _move_power, float _rotate_power)
{
    spinRightMotor(_move_power * 0.75 * getRightCoeff() - 0.5 * _rotate_power);
    spinLefttMotor(_move_power * 0.75 * getLeftCoeff() - 0.5 * _rotate_power);
    spinBackMotor(_move_power * 0.75 * getBackCoeff() - 0.5 * _rotate_power);
}

/**
 * @brief 停止底盘
 */
void stopBase()
{
    stopRightMotor();
    stopLefttMotor();
    stopBackMotor();
}

/**
 * @brief according to velocity direction, return the move distance
 * @return units: mm, from 0 to +infinity
 */
float getForwardPos()
{
    int pos_case = (int(rad2deg(base_vel_heading)) % 180) / 60;
    switch (pos_case)
    {
    case 0:
        return (Sensors::getInstance()->getBasePos(2) / getCoeff(2) + Sensors::getInstance()->getBasePos(1) / getCoeff(1)) / 2.0;
    case 1:
        return (Sensors::getInstance()->getBasePos(1) / getCoeff(1) + Sensors::getInstance()->getBasePos(0) / getCoeff(0)) / 2.0;
    case 2:
        return (Sensors::getInstance()->getBasePos(0) / getCoeff(0) + Sensors::getInstance()->getBasePos(2) / getCoeff(2)) / 2.0;
    default:
        return 0;
    }
}

/**
 * @brief 重置前向位置
 * @return units: mm
 */
void resetForwardPos()
{
    Sensors::getInstance()->resetBasePos();
}

/**
 * @return units: deg
 */
float getHeading()
{
    return Sensors::getInstance()->getBaseRotation();
}

/**
 * @brief 设定胶轮运动方向和速度
 * @param _input 从-100到100，0的时候停转，大于0正转，小于0反转
 */
void spinRoller(float _input)
{
    if (!_input)
        Roller.stop(coast);
    else
        Roller.spin(fwd, _input * 127, voltageUnits::mV);
}

/**
 * @brief 设定机械臂运动方向和速度
 * @param _input 从-100到100，0的时候停转，大于0正转，小于0反转
 */
void spinArm(float _input)
{
    if (!_input)
        Arm.stop(coast);
    else
        Arm.spin(fwd, _input * 127, voltageUnits::mV);
}