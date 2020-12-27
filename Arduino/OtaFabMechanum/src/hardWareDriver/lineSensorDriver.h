/**
 * @file  lineSensorDriver.h
 * @brief ラインセンサの操作を記載
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */


#ifndef LINE_SENSOR_DRIVER_H_INCLUDED
#define LINE_SENSOR_DRIVER_H_INCLUDED

#include <Arduino.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

bool lineSensorInitialize();
String getLineSensorValue();

#endif