/**
 * @file  lineSensorDriver.cpp
 * @brief ラインセンサの操作を記載
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include "lineSensorDriver.h"

#define LINE_SENSOR_DRIVER "[lineSensorSriverLog]:"

bool lineSensorInitialize(){
  pinMode(lineSensorLeftPin, INPUT);
  pinMode(lineSensorCenterPin, INPUT);
  pinMode(lineSensorRightPin, INPUT);
}

String getLineSensorValue(){
  int s0 = digitalRead(lineSensorLeftPin);
  int s1 = digitalRead(lineSensorCenterPin);
  int s2 = digitalRead(lineSensorRightPin);
 
  int sensorvalue=8;
  String senstr = "";

  sensorvalue +=s0*4+s1*2+s2;
  senstr= String(sensorvalue,BIN);
  senstr=senstr.substring(1,4);

  DebugLogPrintln( LINE_SENSOR_DRIVER + __LINE__ +String(__func__)+":" +  senstr);

  return senstr;
}

