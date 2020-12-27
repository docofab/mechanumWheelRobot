/**
 * @file  watchSurrounding.cpp
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include <Arduino.h>

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

#include "./../hardWareDriver/ultraSonicSensor.h"
#include "./../hardWareDriver/servoDriver.h"

#include "functionsApi.h"

const int distancelimit = 30; //distance limit for obstacles in front    
const int sidedistancelimit = 30; //minimum distance in cm to obstacles at both sides (the car will allow a shorter distance sideways)
int leftscanval, centerscanval, rightscanval, ldiagonalscanval, rdiagonalscanval;
  

//Meassures distances to the right, left, front, left diagonal, right diagonal and asign them in cm to the variables rightscanval, 
//leftscanval, centerscanval, ldiagonalscanval and rdiagonalscanval (there are 5 points for distance testing)
String watchSurrounding(){
/*  obstacle_status is a binary integer, its last 5 digits stands for if there is any obstacles in 5 directions,
 *   for example B101000 last 5 digits is 01000, which stands for Left front has obstacle, B100111 means front, right front and right ha
 */
 
  int obstacle_status =B100000;
  centerscanval = ultraSonicSensorWatch();
  if(centerscanval<distancelimit){
    moveStop();
    
    obstacle_status  =obstacle_status | B100;
    }
  servoWrite(120);
  delay(100);
  ldiagonalscanval = ultraSonicSensorWatch();
  if(ldiagonalscanval<distancelimit){
    moveStop();
    
     obstacle_status  =obstacle_status | B1000;
    }
  servoWrite(170); //Didn't use 180 degrees because my servo is not able to take this angle
  delay(300);
  leftscanval = ultraSonicSensorWatch();
  if(leftscanval<sidedistancelimit){
    moveStop();
    
     obstacle_status  =obstacle_status | B10000;
    }

  servoWrite(90); //use 90 degrees if you are moving your servo through the whole 180 degrees
  delay(100);
  centerscanval = ultraSonicSensorWatch();
  if(centerscanval<distancelimit){
    moveStop();
    
    obstacle_status  =obstacle_status | B100;
    }
  servoWrite(40);
  delay(100);
  rdiagonalscanval = ultraSonicSensorWatch();
  if(rdiagonalscanval<distancelimit){
    moveStop();
    
    obstacle_status  =obstacle_status | B10;
    }
  servoWrite(0);
  delay(100);
  rightscanval = ultraSonicSensorWatch();
  if(rightscanval<sidedistancelimit){
    moveStop();
    
    obstacle_status  =obstacle_status | 1;
    }
  servoWrite(90); //Finish looking around (look forward again)
  delay(300);
  String obstacle_str= String(obstacle_status,BIN);
  obstacle_str= obstacle_str.substring(1,6);
  
  return obstacle_str; //return 5-character string standing for 5 direction obstacle status
}

int watchDistance(){
    ultraSonicSensorWatch();
}