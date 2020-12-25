/**
 * @file  moveContllorer.cpp
 * @brief 前後左右の動作を記載、将来的にどっち方向に何cm移動を実装したい
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 * @note 速度と方向のログ周りははそのうちMotorDriverに押し込めて、Contllorerはもっと上層（どっちに何cmうごくとか）にしたほうがよさそう
 */

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

#include "./../hardWareDriver/motorDriver.h"

#include "functionsApi.h"

#define MOTOR_CONTROLLER "[motorContllerLog]:"

static int directionFL = true;//true:foward/false:back.
static int directionFR = true;//true:foward/false:back.
static int directionRL = true;//true:foward/false:back.
static int directionRR = true;//true:foward/false:back.
static int speedFL = 0;//FrontLeftMotorSpeed.
static int speedFR = 0;//FrontRightMotorSpeed.
static int speedRL = 0;//RearLeftMotorSpeed.
static int speedRR = 0;//RearLeftMotorSpeed.

String getDirectionString(int motorDirection){
    if( motorDirection == true ){
        return "fwd";
    }
    return "bck";
}
String getSpeedLog(){
    return ("FL("+getDirectionString(directionFL)+"):"+String(speedFL) +" FR("+getDirectionString(directionFR)+"):"+String(speedFL)+" RL("+getDirectionString(directionRL)+"):"+String(speedRL)+" RR("+getDirectionString(directionRR)+"):"+String(speedRR));
}

/*fwd_bck ラッパー群　ログ取得のためでしかないので将来的にMotorDriverに移動*/
void moveFR_fwd(){
    directionFR = true;
    FR_fwd();
}
void moveFR_bck(){
    directionFR = false;
    FR_bck();
}
void moveFL_fwd(){
    directionFL = true;
    FL_fwd();
}
void moveFL_bck(){
    directionFL = false;
    FL_bck();
}
void moveRR_fwd(){
    directionRR = true;
    RR_fwd();
}
void moveRR_bck(){
    directionRR = false;
    RR_bck();
}
void moveRL_fwd(){
    directionRL = true;
    RL_fwd();
}
void moveRL_bck(){
    directionRL = false;
    RL_bck();
}
/*fwd_bck ラッパー群　ここまで*/

void moveAdvance()  //Forward
{
    moveFR_fwd();
    moveFL_fwd();
    moveRR_fwd();
    moveRL_fwd();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}

void moveTurnLeft()  //Turn left
{
    moveFR_fwd();
    moveFL_bck();
    moveRR_fwd();
    moveRL_bck();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}
void moveTurnRight()  //Turn right
{
    moveFR_bck();
    moveFL_fwd();
    moveRR_bck();
    moveRL_fwd();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}
void moveBack()  //Reverse
{
    moveFR_bck();
    moveFL_bck();
    moveRR_bck();
    moveRL_bck();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}

void moveRightShift(int speed) {
    moveSetSpeed(speed, speed, speed, speed);
    moveFL_fwd(); 
    moveRL_bck(); 
    moveRR_fwd();
    moveFR_bck();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}

void moveLeftShift(int speed){
    moveSetSpeed(speed, speed, speed, speed);
    moveFL_bck();
    moveRL_fwd();
    moveRR_bck();
    moveFR_fwd();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}

void moveRightDiagonalBack(int speed){
    moveSetSpeed(speed, 0, speed, 0);
    moveFL_fwd(); 
    moveRL_bck(); 
    moveRR_fwd();
    moveFR_bck();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}
void moveRightDiagonalAhead(int speed){
    moveSetSpeed(0, speed, 0, speed);
    moveFL_fwd(); 
    moveRL_bck(); 
    moveRR_fwd();
    moveFR_bck();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}
void moveLeftDiagonalBack(int speed){
    moveSetSpeed(speed, 0, speed, 0);
    moveFL_bck();
    moveRL_fwd();
    moveRR_bck();
    moveFR_fwd();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}
void moveLeftDiagonalAhead(int speed){
    moveSetSpeed(0, speed, 0, speed);
    moveFL_bck();
    moveRL_fwd();
    moveRR_bck();
    moveFR_fwd();
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}

void moveStop()
{
    stop_Stop();
    speedFL = 0;
    speedFR = 0;
    speedRL = 0;
    speedRR = 0; 
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}

void moveSetAllSpeed(int speed){
    moveSetSpeed(speed, speed, speed, speed);
    DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  getSpeedLog());
}

void moveSetSpeed(int leftFront,int rightFront,int leftBack,int rightBack){
    speedFL = leftFront;
    speedFR = rightFront;
    speedRL = leftBack;
    speedRR = rightBack; 
    set_Motorspeed(leftFront, rightFront, leftBack, rightBack);
    DebugLogPrintln("setSpeed:" +  getSpeedLog());
}

