/**
 * @file  functionsApi.h 
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#ifndef FUNCTION_APIS_H_INCLUDED
#define FUNCTION_APIS_H_INCLUDED


#include <Arduino.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

void   autoAvoidance();
String watchSurrounding();

/* move */
void moveAdvance();
void moveLeft();
void moveRight();
void moveBack();
void moveStop();
void moveSetSpeed(int leftFront,int rightFront,int leftBack,int rightBack);

#endif
