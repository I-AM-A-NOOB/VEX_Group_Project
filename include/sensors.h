#ifndef SENSORS_H
#define SENSORS_H
#include "v5_vcs.h"
#include "calc.h"
#include "parameters.h"
#include "robot-config.h"
#include "my-timer.h"
using namespace vex;

class Sensors {
private:
    float base_pos[3];
    bool arm_piston_state;
    float base_heading;
    float base_rotation;
    float line_ref[3];
    float arm_rotation;
    Sensors() {};
    ~Sensors() {};
public:
    static Sensors *getInstance(){
        static Sensors *p = NULL;
        if (p == NULL){
            p = new Sensors();
        }
        return p;
    }
    static void deleteInstance(){
        Sensors *p = Sensors::getInstance();
        if(p != NULL){
            delete p;
            p = NULL;
        }
    }
    void updateSens(void);
    bool getArmState(void);
    float getBaseRightPos(void);
    float getBaseLeftPos(void);
    float getBaseBackPos(void);
    float getBasePos(int);
    void resetBaseRightPos(void);
    void resetBaseLeftPos(void);
    void resetBaseBackPos(void);
    void resetBasePos(int);
    void resetBasePos(void);
    float getBaseHeading(void);
    void setBaseHeading(float);
    void resetBaseHeading(void);
    float getBaseRotation(void);
    int getLineRightRef(void);
    int getLineMiddleRef(void);
    int getLineLeftRef(void);
    float getArmRotation();
    void resetArmRotation();
};  

void updateSensors(void);

#endif 