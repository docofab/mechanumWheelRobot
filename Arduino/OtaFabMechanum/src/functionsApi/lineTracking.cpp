/**
 * @file  lineTracking.cpp
 * @brief 
 * 
 * @date 2020/12/24 まずcでファイル分割をかく
 */

#include "./../lib/debugPrint.h"
#include "./../lib/pinAssignment.h"

#include "./../hardWareDriver/lineSensorDriver.h"

#include "functionsApi.h"

#define MID_SPEED 150    
#define HIGH_SPEED 200    
#define LOW_SPEED  100    
#define LONG_DELAY_TIME 70 
#define DELAY_TIME 40 
#define SHORT_DELAY_TIME 30 

void lineracking()
{
  String senstr="";

  senstr = getLineSensorValue();

  if ( senstr=="100" )
  {
    DebugLogPrintln(" Shift Left");
    moveSharpTurnLeft(LOW_SPEED,MID_SPEED);
    //  left_shift(HIGH_SPEED,HIGH_SPEED,HIGH_SPEED,HIGH_SPEED);
    delay(DELAY_TIME);
    moveStop();     
  }
   
  if ( senstr=="110" )
  {
    DebugLogPrintln("Slight Shift Left");
    moveCurve(0,HIGH_SPEED);
    delay(DELAY_TIME);
    moveStop(); 
  }
 
  if (senstr=="010" || senstr=="101"  )
  {
    // DebugLogPrintln("moveCurve");
    moveCurve(MID_SPEED,MID_SPEED);
    delay(DELAY_TIME);
    moveStop(); 
  }
  if (senstr=="011")
  {    
    //DebugLogPrintln("Slight Shift to Right ");
    moveCurve(HIGH_SPEED,0);
    delay(DELAY_TIME);
    moveStop(); 
  }
  if (senstr=="001")
  {
    //  DebugLogPrintln("Shift to Right");
    moveSharpTurnRight(MID_SPEED,LOW_SPEED);
    //  right_shift(HIGH_SPEED,HIGH_SPEED,HIGH_SPEED,HIGH_SPEED);
    delay(DELAY_TIME);
    moveStop();       
  }
  if (senstr=="000"){
    moveSetAllSpeed(MID_SPEED);
    moveBack();
    delay(DELAY_TIME/2*3);
    moveStop();  
  }
  if (senstr=="111")
  {
    //  DebugLogPrintln("Sharp Right U Turn");
    moveSharpTurnRight(MID_SPEED,MID_SPEED);
    delay(DELAY_TIME);
    moveStop();     
  }
}
