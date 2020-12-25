# mechanumWheelRobot

Arduino Mecanum Omni Direction Wheel Robot Carを研究するリポジトリです。

CopyRight www.osoyoo.com

```
/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car
 * Tutorial URL http://osoyoo.com/?p=30022
 * CopyRight www.osoyoo.com
*/
```

## 製品のページ

[Metal Chassis Mecanum Wheel Robotic (for Arduino Mega2560)](https://osoyoo.com/2019/11/08/omni-direction-mecanum-wheel-robotic-kit-v1/)

## マニュアル

https://osoyoo.com/manual/V1.2metal_mecanumcar.pdf

## Arduino IDE用のスケッチ

* [Lesson 1 Basic Robot Car Assembling（基本ロボットカーの組み立て・動作確認）](http://osoyoo.com/driver/mecanum_metal_chassis/for_mega2560/metal-2560-lesson1.zip)
* [Lesson 2 Obstacle Avoidance Robot Car（障害物回避）](http://osoyoo.com/driver/mecanum_metal_chassis/for_mega2560/metal-2560-lesson2.zip)
* [Lesson 3 Line Following Robot Car（ライントレース）](http://osoyoo.com/driver/mecanum_metal_chassis/for_mega2560/metal-2560-lesson3.zip)
* [Lesson 4 Bluetooth Controlled Imitation Driving（Bluetooth制御）](http://osoyoo.com/driver/mecanum_metal_chassis/for_mega2560/metal-2560-lesson4.zip)
* [Lesson 5 Wifi Controlled Robot Car（WiFi制御）](http://osoyoo.com/driver/mecanum_metal_chassis/for_mega2560/metal-2560-lesson5.zip)

## Fork後のフォルダ構成

```
mechanumWheelRobot
├ src
│   ├functionApi　   //機能を記載(ロボット全体の動きが責務)
│   │   ├autoAvoidance.cpp
│   │   ├functionApi.h
│   │   ├moveContllorer.cpp
│   │   ├moveContllorer.h
│   │   ├moveTest.cpp
│   │   ├watchSurrounding.cpp
│   ├hardWareDriver //モーター、センサの駆動・値取得を記載（動きとセンサ値が責務）
│   │   ├motorDriver.cpp
│   │   ├motorDriver.h
│   │   ├servoDriver.cpp
│   │   ├servoDriver.h
│   │   ├ultraSonicSensor.cpp
│   │   ├ultraSonicSensor.h
│   ├lib　　　　　　 //ピンアサイン・デバッグ出力を記載（全体で共通に用いる便利関数、定義などを記載）
│   │   ├debugPrint.cpp
│   │   ├debugPrint.h
│   │   ├pinAssignment.h
├ LICENCE
├ README.md
└ mechanumWheelRobot.ino
```
