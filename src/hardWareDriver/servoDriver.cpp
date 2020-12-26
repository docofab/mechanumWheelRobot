/**
 * @file  servoDriver.cpp
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include "servoDriver.h"

Servo head;

/**
 * @brief サーボモータの初期化
 * @note : 初期化動作 0度⇒170度⇒90度：
 */
void servoInit(){ 
  head.attach(SERVO_PIN); 
  servoWrite(0);
  delay(1000);
  servoWrite(170);
  delay(1000);
  servoWrite(90);
  delay(2000);
}

static int servoPosition = 90;
void servoWrite(int angle){
  if(angle < 0 && 170 < angle ){
      return;
  }
  head.write(angle);
  servoPosition = angle;
}

int getServoPosition(){
  return servoPosition;
}