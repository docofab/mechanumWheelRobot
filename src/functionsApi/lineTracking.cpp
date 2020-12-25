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

void lineracking()
{
  String senstr="";

  senstr = getlineSensorValue();

  if ( senstr=="100" )
  {
    DebugLogPrintln(" Shift Left");
    sharpLeftTurn(LOW_SPEED,MID_SPEED);
    //  left_shift(HIGH_SPEED,HIGH_SPEED,HIGH_SPEED,HIGH_SPEED);
    delay(DELAY_TIME);
    stop_bot();     
  }
   
  if ( senstr=="110" )
  {
    DebugLogPrintln("Slight Shift Left");
    forward(0,HIGH_SPEED);
    delay(DELAY_TIME);
    stop_bot(); 
  }
 
  if (senstr=="010" || senstr=="101"  )
  {
    // DebugLogPrintln("Forward");
    forward(MID_SPEED,MID_SPEED);
    delay(DELAY_TIME);
    stop_bot(); 
  }
  if (senstr=="011")
  {    
    //DebugLogPrintln("Slight Shift to Right ");
    forward(HIGH_SPEED,0);
    delay(DELAY_TIME);
    stop_bot(); 
  }
  if (senstr=="001")
  {
    //  DebugLogPrintln("Shift to Right");
    sharpRightTurn(MID_SPEED,LOW_SPEED);
    //  right_shift(HIGH_SPEED,HIGH_SPEED,HIGH_SPEED,HIGH_SPEED);
    delay(DELAY_TIME);
    stop_bot();       
  }
  if (senstr=="000"){
    reverse(MID_SPEED);
    delay(DELAY_TIME/2*3);
    stop_bot();  
  }
  if (senstr=="111")
  {
    //  DebugLogPrintln("Sharp Right U Turn");
    sharpRightTurn(MID_SPEED,MID_SPEED);
    delay(DELAY_TIME);
    stop_bot();     
  }
}