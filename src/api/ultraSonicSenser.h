/**
 * @file  ultraSonicSenser.h
 * @brief 
 * 
 * @date 
 */

#ifndef ULTRASONIC_SENSOR_H_INCLUDED
#define ULTRASONIC_SENSOR_H_INCLUDED

#include <Arduino.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

bool ultraSonicSensorInitialize();
int ultraSonicSensorWatch();

#endif
