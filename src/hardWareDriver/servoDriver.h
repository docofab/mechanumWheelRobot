/**
 * @file  servoDriver.h 
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 *                  Servoクラスがすでにあるので少し筋悪かもしれない
 */

#ifndef SERVO_DRIVER_H_INCLUDED
#define SERVO_DRIVER_H_INCLUDED

#include <Servo.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

void servoInit();
void servoWrite(int angle);
int getServoPosition();
void servoSmoothWrite(int angle,int division,int delay_mseconds);
#endif
