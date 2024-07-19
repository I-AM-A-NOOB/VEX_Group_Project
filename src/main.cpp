/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       w2j                                                       */
/*    Created:      2024/7/15 15:22:24                                        */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "robot-config.h"
#include "iostream"
#include "vex.h"
#include "controller.h"
#include "sensors.h"
#include "basic-functions.h"
#include "auton-function.h"
#include "PID.h"
using namespace vex;

// A global instance of competition
competition Competition;
// brain Brain;
//  define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

/// @brief 自动化之前执行

void pre_auton(void)
{
    Imu.calibrate();
    Controller1.Screen.print("君其毋急");
    while (Imu.isCalibrating())
    {
        wait(100, msec);
    }
    Controller1.Screen.clearLine();
    Controller1.Screen.print("战斗！爽！");
}
void triRotateAbs(int deg)
{ // 三回啊三回
    for (int i = 0; i < 11; i++)
    {
        pidRotateAbs(deg);
    }
}

void posForwardAbsRevision(int target, int division, int deg)
{
    for (int i = 1; i <= division; i++)
    {
        posForwardAbs(60, target / division);
        triRotateAbs(deg);
    }
}

void blue2green(void)
{
    // setBaseVelHeading(deg2rad(90));
    triRotateAbs(90);
    resetForwardPos();
    /// softStartTimerForward(30, 100, 1);
    //  for(int i = 1; i <= 8; i++) {
    //  triRotateAbs(90);
    //  posForwardAbs(60, 307);
    // }
    posForwardAbsRevision(2400, 4, 90);
    stopBase();
}
void green2blue(void)
{
    triRotateAbs(-90);
    // setBaseVelHeading(deg2rad(90));
    resetForwardPos();
    // for(int i = 1; i <= 8; i++) {
    // posForwardAbs(60, 307);
    // triRotateAbs(-90);
    // }
    posForwardAbsRevision(2430, 4, -90);
}

void dropball(void)
{
    triRotateAbs(-90);
    setArmEvent(ArmEvent::score_low);
    spinRoller(-800);
    triRotateAbs(-90);
    stopBase();
    wait(1000, msec);
    setArmEvent(ArmEvent::reposition);
    spinRoller(400);
    triRotateAbs(-90);
}
void throwball()
{
    triRotateAbs(-45);
    setArmEvent(ArmEvent::reposition);
    spinRoller(-1400);
    wait(200, msec);
    setArmEvent(ArmEvent::reposition);
    spinRoller(400);
}
void fetchball()
{
    triRotateAbs(90);
    setArmEvent(ArmEvent::reposition);
    wait(5000, msec);
    //setArmEvent(ArmEvent::reposition);
}
int red2green(void)
{
    int length[3] = {1050, 730, 1400}; // 第一段，几字横，几字竖
    // 绿红绿往返
    // green to red
    // printf("1");
    // setBaseVelHeading(deg2rad(90));
    // 绿到第一个拐角
    triRotateAbs(180);
    resetForwardPos();
    softStartTimerForward(50, 100, 1);
    for (int i = 1; i <= 3; i++)
    {
        posForwardAbs(50, (length[0] / 3));
        triRotateAbs(180);
    }
    stopBase();
    wait(200, msec);
    // 几字第一段
    triRotateAbs(-90);
    resetForwardPos();
    softStartTimerForward(50, 100, 1);
    for (int i = 1; i <= 3; i++)
    {
        posForwardAbs(50, (length[2] / 3));
        triRotateAbs(-90);
    }
    stopBase();
    wait(200, msec);
    // 几字第二段
    triRotateAbs(180);
    // setBaseVelHeading(deg2rad(90));
    resetForwardPos();
    softStartTimerForward(50, 100, 1);
    for (int i = 1; i <= 3; i++)
    {
        posForwardAbs(50, (length[1] / 3));
        triRotateAbs(180);
    }
    stopBase();
    wait(100, msec);
    // 几字第三段
    triRotateAbs(90);
    // setBaseVelHeading(deg2rad(90));
    resetForwardPos();
    softStartTimerForward(50, 100, 1);
    for (int i = 1; i <= 3; i++)
    {
        posForwardAbs(50, (length[2] / 3));
        triRotateAbs(90);
    }
    stopBase();
    wait(900, msec);

    fetchball();

    triRotateAbs(-90);
    // turn to green
    // setBaseVelHeading(deg2rad(90));
    resetForwardPos();
    softStartTimerForward(50, 100, 1);
    for (int i = 1; i <= 3; i++)
    {
        posForwardAbs(50, (length[2] / 3));
        triRotateAbs(-90);
    }
    wait(500, msec);
    triRotateAbs(0);

    // setBaseVelHeading(deg2rad(90));
    resetForwardPos();
    softStartTimerForward(50, 100, 1);
    for (int i = 1; i <= 3; i++)
    {
        posForwardAbs(50, ((length[1]-10) / 3));
        triRotateAbs(0);
    }
    wait(500, msec);
    triRotateAbs(90);
    //此处throw红球！
    //throwball();
    // nonono,void beautifulRooster();美丽公鸡？
    //扔完红球可以直接拿绿球（





    // setBaseVelHeading(deg2rad(90));
    resetForwardPos();
    softStartTimerForward(50, 100, 1);
    for (int i = 1; i <= 3; i++)
    {
        posForwardAbs(50, (length[2] / 3));
        triRotateAbs(90);
    }
    wait(500, msec);
    triRotateAbs(0);

    // setBaseVelHeading(deg2rad(90));
    resetForwardPos();
    softStartTimerForward(50, 100, 1);
    posForwardAbs(50, length[0] + 30); // revision
    wait(500, msec);
    return 1;
}

void autonomous(void)
{
    // 从yellow到blue
    //  等陀螺仪
    wait(2000, msec);
    setArmEvent(ArmEvent::reposition);
    setBaseVelHeading(deg2rad(90));
    resetForwardPos();
    softStartTimerForward(30, 60, 10);
    triRotateAbs(0);
    triRotateAbs(0);
    posForwardAbs(60, 2470);
    // for(int i=1;i<=3;i++){
    //     blue2green();
    //     fetchball();
    //     green2blue();
    //     dropball();
    // }

    while (1)
    {
        // green
        blue2green();
        fetchball();
        green2blue();
        dropball();
        // green
        blue2green();
        fetchball();
        green2blue();
        dropball();
        // red
        blue2green();
        red2green();
        green2blue();
        dropball();
        // green
        blue2green();
        fetchball();
        green2blue();
        dropball();
        // green
        blue2green();
        fetchball();
        green2blue();
        dropball();
        // red
        blue2green();
        red2green();
        green2blue();
        dropball();
        // green
        blue2green();
        fetchball();
        green2blue();
        dropball();
    }

        // //以下整活：勿管，会注释掉
    // while(1){
    //     blue2green();
    //     fetchball();
    //     green2blue();
    //     dropball();
    //     blue2green();
    //     red2green();
    //     fetchball();
    //     green2blue();
    //     dropball();
    // }

    
}

/// @brief 手动操作
/// @param  使用摇杆控制
void usercontrol(void)
{
    // User control code here, inside the loop

    // while (1) {
    // if(R1){autonomous();}
    // wait(20, msec);
    // }
    // 自动调试

    while (1)
    {
        defineController();
        // Base[1].spin(fwd,A2*60+A1*50,voltageUnits::mV);
        // Base[2].spin(fwd,A2*60-A1*50,voltageUnits::mV);
        // Base[0].spin(fwd,A1*50,voltageUnits::mV);
        Brain.Screen.setCursor(2, 1);
        Brain.Screen.print("Inertial(heading deg): %5.2f", Sensors::getInstance()->getBaseHeading());
        setGlobalVelHeading(deg2rad(calDir(A4, A3)));

        // setBaseVelHeading(deg2rad(calDir(A4, A3)));
        if (calMod(A4, A3) > 5 || abs(A1) > 5)
        {
            moveBaseWithRotate(calMod(A4, A3), A1);
        }
        else
        {
            stopBase();
        }
        // roller controll
        if (R1 || R2)
        {
            spinRoller(-800);
        }
        else
        {
            spinRoller(400);
        }

        if (L1)
        {
            if (getArmState() == ArmState::init)
                setArmEvent(ArmEvent::take_item);
            else if (getArmState() == ArmState::ready)
                setArmEvent(ArmEvent::score_low);
            else if (getArmState() == ArmState::low)
                setArmEvent(ArmEvent::score_high);
        }
        else if (L2)
        {
            setArmEvent(ArmEvent::reposition);
        }
        if (DOWN && !last_DOWN)
        {
            setArmEvent(ArmEvent::reset_encoder);
        }

        if (A && !last_A)
            autonomous();
        wait(20, msec);
    }
}
/// @brief 主函数
/// @return 0
int main()
{
    thread AutonArm(autonArm);
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    Sensors *ps = Sensors::getInstance();
    thread AutonSensor(updateSensors);
    pre_auton();

    while (true)
    {
        wait(100, msec);
    }
}
