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

#define SPEED 140    
#define TURN_SPEED 160    

void moveTest(){

    moveAdvance(SPEED);
        delay(1000);
        stop_Stop();
        delay(1000);
    
    moveBack(SPEED);
        delay(1000);
        stop_Stop();
        delay(1000);
        
    moveTrunLeft(TURN_SPEED);
        delay(1000);
        stop_Stop();
        delay(1000);
        
    right_turn(TURN_SPEED);
        delay(1000);
        stop_Stop();
        delay(1000);
    
    right_shift(200,200,200,200); //right shift
        delay(1000);
        stop_Stop();
        delay(1000);

    left_shift(200,200,200,200); //left shift
        delay(1000);
        stop_Stop();
        delay(1000);
        
    left_shift(200,0,200,0); //left diagonal back
        delay(1000);
        stop_Stop();
        delay(1000);
    
    right_shift(200,0,200,0); //right diagonal ahead
        delay(1000);
        stop_Stop();
        delay(1000);

    left_shift(0,200,0,200); //left diagonal ahead
        delay(1000);
        stop_Stop();
        delay(1000);

    right_shift(0,200,0,200); //right diagonal back
        delay(1000);
        stop_Stop();
        delay(1000);
}