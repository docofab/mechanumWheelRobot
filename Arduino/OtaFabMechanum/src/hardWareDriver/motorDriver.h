/**
 * @file  motorDriver.h 
 * @brief モーターを動作させるものはここに記載
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#ifndef MOTOR_DRIVER_H_INCLUDED
#define MOTOR_DRIVER_H_INCLUDED

#include <Arduino.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

bool motorInitialize();
bool motorHWpinInitilalize();


void stop_Stop();
void set_Motorspeed(int leftFront,int rightFront,int leftBack,int rightBack);

void FR_fwd();
void FR_bck();
void FL_fwd();
void FL_bck();
void RR_fwd();
void RR_bck();
void RL_fwd();
void RL_bck();

#endif

