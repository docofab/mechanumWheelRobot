/**
 * @file  autoAvoidance.cpp
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include <Arduino.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

#include "functionsApi.h"

#define MOVETEST_SPEED 140    
#define MOVETEST_TURN_SPEED 160    
#define MOVETEST_SHIFT_SPEED 200

void moveTest(){
    moveSetAllSpeed(MOVETEST_SPEED);
    moveAdvance();
    delay(1000);
    moveStop();
    delay(1000);
    moveSetAllSpeed(MOVETEST_SPEED);
    moveBack();
    delay(1000);
    moveStop();
    delay(1000);
    moveSetAllSpeed(MOVETEST_TURN_SPEED);
    moveTurnLeft();
    delay(1000);
    moveStop();
    delay(1000);
    moveSetAllSpeed(MOVETEST_TURN_SPEED);    
    moveTurnRight();
    delay(1000);
    moveStop();
    delay(1000);

    moveRightShift(MOVETEST_SHIFT_SPEED);//right shift
    delay(1000);
    moveStop();
    delay(1000);

    moveLeftShift(MOVETEST_SHIFT_SPEED); //left shift
    delay(1000);
    moveStop();
    delay(1000);
        
    moveLeftDiagonalBack(MOVETEST_SHIFT_SPEED); //left diagonal back
    delay(1000);
    moveStop();
    delay(1000);
    
    moveRightDiagonalAhead(MOVETEST_SHIFT_SPEED); //right diagonal ahead
    delay(1000);
    moveStop();
    delay(1000);

    moveLeftDiagonalAhead(MOVETEST_SHIFT_SPEED); //left diagonal ahead
    delay(1000);
    moveStop();
    delay(1000);

    moveRightDiagonalBack(MOVETEST_SHIFT_SPEED); //right diagonal back
    delay(1000);
    moveStop();
    delay(1000);
}