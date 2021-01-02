/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car
 * Tutorial URL http://osoyoo.com/?p=30022
 * CopyRight www.osoyoo.com
*/

#include <ros.h>
#include <geometry_msgs/Twist.h>

ros::NodeHandle nh;
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb);

#include "src/lib/pinAssignment.h"
#include "src/lib/debugPrint.h"

#include "src/hardWareDriver/motorDriver.h"
#include "src/hardWareDriver/servoDriver.h"
#include "src/hardWareDriver/ultraSonicSensor.h"

#include "src/functionsApi/functionsApi.h"

void messageCb(const geometry_msgs::Twist& twist) {
  const float linear_x = twist.linear.x;
  const float angle_z = twist.angular.z;
  if (linear_x > 0.0 && angle_z == 0.0) {
    // Go forward
    moveAdvance();

  } else if (linear_x < 0.0 && angle_z == 0.0) {
    // Go back
    moveBack();

  } else if (angle_z > 0.0) {
    if (linear_x == 0) {
      // Turn left
      moveTurnLeft();
    } else if (linear_x > 0) {
      // Go left forward
      moveLeftDiagonalAhead(200);
    } else {
      // Go right back
      moveRightDiagonalBack(200);
    }
  } else if (angle_z < 0.0) {
    if (linear_x == 0) {
      // Turn right
      moveTurnRight();
    } else if (linear_x > 0) {
      // Go right forward
      moveRightDiagonalAhead(200);
    } else {
      // Go left back
      moveLeftDiagonalBack(200);
    }
  } else {
    // stop
    moveStop();
  }
}

void setup() {
    /* motor initilize */
    motorInitialize();
    moveStop();//stop move

    /*init servo*/
    servoInit();

    /*init HC-SR04*/
    ultraSonicSensorInitialize();

    nh.getHardware()->setBaud(115200);
    nh.initNode();
    nh.subscribe(sub);
 
    moveStop();//Stop
 
}

void loop() {
   // autoAvoidance();
    // Serial.println( watchsurrounding());
    nh.spinOnce();
    delay(1);
}
