/**
 * @file  moveContllorer.cpp
 * @brief 前後左右の動作を記載、将来的にどっち方向に何cm移動を実装したい
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

#include "./../hardWareDriver/motorDriver.h"

#define MOTOR_CONTROLLER "[motorContllerLog]:"

static int speedFL = 0;//FrontLeftMotorSpeed.
static int speedFR = 0;//FrontRightMotorSpeed.
static int speedRL = 0;//RearLeftMotorSpeed.
static int speedRR = 0;//RearLeftMotorSpeed.

String getSpeedLog(){
    return ("FL:"+String(speedFL) +" FR:"+String(speedFL)+" RL:"+String(speedRL)+" RR:"+String(speedRR));
}

void moveAdvance()  //Forward
{
    FR_fwd();
    FL_fwd();
    RR_fwd();
    RL_fwd();
    DbugPrintln( MOTOR_CONTROLLER + __LINE__ +"moveAdvance:" +  getSpeedLog());
}

void moveTurnLeft()  //Turn left
{
    FR_fwd();
    FL_bck();
    RR_fwd();
    RL_bck();
    DbugPrintln( MOTOR_CONTROLLER + __LINE__ +"moveTrunLeft:" +  getSpeedLog());
}
void moveTurnRight()  //Turn right
{
    FR_bck();
    FL_fwd();
    RR_bck();
    RL_fwd();
    DbugPrintln( MOTOR_CONTROLLER + __LINE__ +"moveTrunRight:" +  getSpeedLog());
}
void moveBack(int speed)  //Reverse
{
    FR_bck();
    FL_bck();
    RR_bck();
    RL_bck();
    DbugPrintln( MOTOR_CONTROLLER + __LINE__ +"moveBack:" +  getSpeedLog());
}
void moveStop()
{
    stop_Stop();
    speedFL = 0;
    speedFR = 0;
    speedRL = 0;
    speedRR = 0; 
    DbugPrintln( MOTOR_CONTROLLER + __LINE__ +"moveStop:" +  getSpeedLog());
}

void moveRightShift(int speed) {
    setMotorspeed(speed, speed, speed, speed);
    FL_fwd(); 
    RL_bck(); 
    RR_fwd();
    FR_bck();
    DbugPrintln( MOTOR_CONTROLLER + __LINE__ +"moveRightShift:" +  getSpeedLog());
}

void moveLeftShift(int speed){
    setMotorspeed(speed, speed, speed, speed);
    FL_bck();
    RL_fwd();
    RR_bck();
    FR_fwd();
    DbugPrintln( MOTOR_CONTROLLER + __LINE__ +"moveLeftShift:" +  getSpeedLog());
}

void moveSetAllSpeed(int speed){
    setMotorspeed(speed, speed, speed, speed);
    DbugPrintln( MOTOR_CONTROLLER + "setALllSpeed:" +  getSpeedLog());
}

void moveSetSpeed(int leftFront,int rightFront,int leftBack,int rightBack){
    speedFL = leftFront;
    speedFR = rightFront;
    speedRL = leftBack;
    speedRR = rightBack; 
    set_Motorspeed(leftFront, rightFront, leftBack, rightBack);
    DbugPrintln("setSpeed:" +  getSpeedLog());
}
