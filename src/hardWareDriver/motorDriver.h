/**
 * @file  motorController.h 
 * @brief モーターを動作させるものはここに記載
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#ifndef MOTOR_CONTROLLER_H_INCLUDED
#define MOTOR_CONTROLLER_H_INCLUDED

#include <Arduino.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

bool motorInitialize();
bool motorHWpinInitilalize();

#endif

