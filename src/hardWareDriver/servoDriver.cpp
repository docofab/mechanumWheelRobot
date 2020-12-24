/**
 * @file  servoDriver.cpp
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include "servoDriver.h"

Servo head;

void servoInit(){ 
  head.attach(SERVO_PIN); 
  servoWrite(0);
  delay(1000);
  servoWrite(170);
  delay(1000);
  servoWrite(90);
  delay(2000);
}

void servoWrite(int angle){
  if(angle < 0 && 170 < angle ){
      return;
  }
  head.write(angle);
}