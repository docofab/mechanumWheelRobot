/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car
 * Tutorial URL http://osoyoo.com/?p=30022
 * CopyRight www.osoyoo.com
*/

#include "src/lib/pinAssignment.h"
#include "src/lib/debugPrint.h"

#include "src/hardWareDriver/motorDriver.h"
#include "src/hardWareDriver/servoDriver.h"
#include "src/hardWareDriver/ultraSonicSenser.h"

#include ""

void setup() {

　/* motor initilize */
  motorInitialize();
  stop_Stop();//stop move

  /*init servo*/
  servoInit();

  /*init HC-SR04*/
  ultraSonicSensorInitialize();

  Serial.begin(9600);
 
  stop_Stop();//Stop
 
}

void loop() {
auto_avoidance();
// Serial.println( watchsurrounding());
}
