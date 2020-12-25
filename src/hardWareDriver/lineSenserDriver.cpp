/**
 * @file  lineSensorDriver.cpp
 * @brief ラインセンサの操作を記載
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include "lineSensorDriver.h"

bool lineSensorInitialize(){
  pinMode(lineSensorLeftPin, INPUT);
  pinMode(lineSensorCenterPin, INPUT);
  pinMode(lineSensorRightPin, INPUT);
}

String getlineSensorValue(){
  int s0 = digitalRead(lineSensorLeftPin);
  int s1 = digitalRead(lineSensorCenterPin);
  int s2 = digitalRead(lineSensorRightPin);
 
  int sensorvalue=8;
  sensorvalue +=s0*4+s1*2+s2;
  senstr= String(sensorvalue,BIN);
  senstr=senstr.substring(1,4);

  DebugLogPrintln( MOTOR_CONTROLLER + __LINE__ +String(__func__)+":" +  senstr);

  return sensstr;
}

