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

/* function */
void autoAvoidance();

/* watch */
String watchSurrounding();
int watchDistance();

/* move */
void moveAdvance();
void moveTurnLeft();
void moveTurnRight();
void moveBack();

void moveRightShift(int speed);
void moveLeftShift(int speed);

void moveRightDiagonalBack(int speed);
void moveRightDiagonalAhead(int speed);
void moveLeftDiagonalBack(int speed);
void moveLeftDiagonalAhead(int speed);

void moveStop();
void moveSetAllSpeed(int speed);
void moveSetSpeed(int leftFront,int rightFront,int leftBack,int rightBack);

#endif
