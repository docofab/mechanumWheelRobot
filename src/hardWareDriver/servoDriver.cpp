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

void servoSmoothWrite(int angle,int division,int delay_mseconds){
  if(angle < 0 && 170 < angle ){
      return;
  }
  if(division <= 0){
    DebugLogPrintln("Zero Division...");
    return;
  }
  if(delay <= 0){
    DebugLogPrintln("Iligal input...");
    return;
  }
  int current_angle = getServoPosition();
  int target_angle = angle;
  int diff = target_angle - current_angle;
  int dir = diff / abs(diff);
  int move_times = abs(diff) / division;
  for(int i = 0; i < move_times - 1; i++){
    current_angle = current_angle + dir * division;
    servoWrite(current_angle);
    //DebugLogPrintln("current_angle:"+String(current_angle));
    delay(delay_mseconds);
  }
  servoWrite(target_angle);

  servoPosition = angle;
}

int getServoPosition(){
  return servoPosition;
}