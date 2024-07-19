#include "my-timer.h"
#include "vex.h"
#include "robot-config.h"

/**
 * @brief 初始化timer函数
*/
MyTimer::MyTimer()
{
    startTime = Brain.Timer.value();
}

/**
 * @brief 重置timer
*/
void MyTimer::reset()
{
    startTime = Brain.Timer.value();
}

/**
 * @brief 获取当前时间
 * @return 返回当前时间，单位：毫秒（msec）
*/
int MyTimer::getTime() const
{
    return floor((Brain.Timer.value() - startTime) * 1000); // return time (msec) from startTime
}

/**
 * @brief 获取当前时间
 * @return 返回当前时间，单位：秒（sec）
*/
double MyTimer::getTimeDouble() const
{
    return Brain.Timer.value() - startTime; // return time (sec) from startTime
}