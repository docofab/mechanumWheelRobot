/**
 * @file  autoAvoidance.cpp
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include <Arduino.h>

#include "functionsApi.h"

#define LPT 2 // scan loop coumter

#define FAST_SPEED  160   //both sides of the motor speed
#define SPEED  120     //both sides of the motor speed
#define TURN_SPEED  120   //both sides of the motor speed
#define BACK_SPEED1  160   //back speed
#define BACK_SPEED2  90    //back speed

int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
const int distancelimit = 30; //distance limit for obstacles in front           
const int sidedistancelimit = 30; //minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)
int distance;
int numcycles = 0;
const int turntime = 250; //Time the robot spends turning (miliseconds)
const int backtime = 300; //Time the robot spends turning (miliseconds)

int thereis;
void autoAvoidance(){

  ++numcycles;
  if(numcycles>=LPT){ //Watch if something is around every LPT loops while moving forward 
    moveStop();
    String obstacle_sign = watchSurrounding(); // 5 digits of obstacle_sign binary value means the 5 direction obstacle status
    
    DebugLogPrintln("begin str="+obstacle_sign);
    if( obstacle_sign=="10000" ){
      DebugLogPrintln("SLIT Right");
      moveSetSpeed(FAST_SPEED,SPEED,FAST_SPEED,SPEED);
      moveAdvance();
      delay(turntime);
      moveStop();
    }else
    if( obstacle_sign=="00001" ){
      DebugLogPrintln("SLIT Left");
      moveSetSpeed(SPEED,FAST_SPEED,SPEED,FAST_SPEED);
      moveAdvance();
  
      delay(turntime);
      moveStop();
    }else 
    if( obstacle_sign=="11100" || 
        obstacle_sign=="01000" || 
        obstacle_sign=="11000" || 
        obstacle_sign=="10100" || 
        obstacle_sign=="01100" ||
        obstacle_sign=="00100" ||
        obstacle_sign=="01000" )
    {
      DebugLogPrintln("hand right");
	  moveRight();
      moveSetSpeed(TURN_SPEED,TURN_SPEED,TURN_SPEED,TURN_SPEED);
      delay(turntime);
      moveStop();
    }else 
    if( obstacle_sign=="00010" || 
        obstacle_sign=="00111" || 
        obstacle_sign=="00011" || 
        obstacle_sign=="00101" || 
        obstacle_sign=="00110" || 
        obstacle_sign=="01010" )
    {
      DebugLogPrintln("hand left");
      moveLeft();//Turn left
      moveSetSpeed(TURN_SPEED,TURN_SPEED,TURN_SPEED,TURN_SPEED);
      delay(turntime);
      moveStop();
    }else 
    if(  obstacle_sign=="01111" ||
         obstacle_sign=="10111" ||
         obstacle_sign=="11111"  )
    {
      DebugLogPrintln("hand back left");
	  moveBack();
	  moveSetSpeed( BACK_SPEED1,BACK_SPEED2,BACK_SPEED1,BACK_SPEED2);
      delay(backtime);
      moveStop();
    }else 
    if( obstacle_sign=="11011"  ||
        obstacle_sign=="11101"  ||
        obstacle_sign=="11110"  || 
        obstacle_sign=="01110"  )
    {
      DebugLogPrintln("hand back right");
      moveBack();
      moveSetSpeed(BACK_SPEED2,BACK_SPEED1,BACK_SPEED2,BACK_SPEED1);
      delay(backtime);
      moveStop();
    }else{
      DebugLogPrintln("no handle");
    }

    numcycles=0; //Restart count of cycles
  } else {
      moveSetSpeed(SPEED,SPEED,SPEED,SPEED);
      moveAdvance();  // if nothing is wrong go forward using go() function above.
      delay(backtime);
      moveStop();
  }
  
  //else  Serial.println(numcycles);
  
  distance = watch(); // use the watch() function to see if anything is ahead (when the robot is just moving forward and not looking around it will test the distance in front)
  if (distance<distancelimit){ // The robot will just stop if it is completely sure there's an obstacle ahead (must test 25 times) (needed to ignore ultrasonic sensor's false signals)
    DebugLogPrintln("final go back");
	moveBack();
    moveSetSpeed(BACK_SPEED1,BACK_SPEED2,BACK_SPEED1,BACK_SPEED2);
    delay(backtime);
    ++thereis;
  }
  
  if (distance>distancelimit){
      thereis=0;
  } //Count is restarted

  if (thereis > 25){
  Serial.println("final stop");
    moveStop(); // Since something is ahead, stop moving.
    thereis=0;
  }
}