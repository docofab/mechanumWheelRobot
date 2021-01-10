# Lesson1

## 目的とする動作

1. 前進して2秒間後退
1. 左折と右折を2秒間
1. 右真横と左真横に2秒間
1. 左斜め後方と右斜め前方に2秒間
1. 左斜め前方と右斜め後方に2秒間
1. 停止

## ソースコード

* [metal-2560-lesson1.ino](/Arduino/osoyoo/metal-2560-lesson1/metal-2560-lesson1.ino)

## ハードウェア

* マイコン [OSOYOO MEGA2560 R3 Control Board ATMEGA2560-16AU USB Cable (compatible with Arduino)](https://osoyoo.store/products/osoyoo-mega2560-r3-control-board-atmega2560-16au-usb-cable-compatible-with-arduino?variant=31180322078831)
  * 特徴
    1. Microcontroller: ATmega2560
    1. Operating Voltage: 5V
    1. Digital I/O Pins: 54 (of which 14 provide PWM output)
    1. Analog Input Pins: 16
    1. DC Current per I/O Pin: 40 mA
    1. DC Current for 3.3V Pin: 50 mA
* モータードライバ [OSOYOO Model-X Motor Driver Module](https://osoyoo.com/2017/08/15/osoyoo-model-x-motor-driver-module/)
  * 特徴
    1. モーター駆動電圧：5-35V、制御電圧：5V
    1. 最大定格 40V, 3A, 25W

* モーター [DC Encoder Motor Robotic Car Speed Encoder 9V for Arduino Raspberry Pi Platform DIY](https://osoyoo.store/products/dc-motor-robotic-car-speed-encoder-9v-for-arduino-raspberry-pi-platform-diy?variant=31930889830511)
  * 特徴
    1. 標準定格電圧 DC 9.0V
    1. モーター無負荷時回転数：11500±10% rpm
    1. ギヤモーター回転数：150±10% rpm
  * 信号線は6本
    1. モーター電源/GND
    1. ホールセンサー電源/GND
    1. ホールセンサー出力1/出力2   

## モータの配置

* 上からみた図。
* Left Model X, Right Model Xはモータードライバ基板
)
* Mがモーター

```
                FRONT
      LEFT                RIGHT
        --M  R-K3    R-K1  M--  

  (Left Model X)     (Right Model X)

        --M  L-K1    L-K3  M--  

                 REAR 
```

## Arduinoで使用する出力ピン

* 出力ピンの初期化は void init_GPIO() 関数で行っています。

|定数名|Arduinoピン番号|信号の向き|役割|
|-----|--------------|--------|---|
|speedPinR|9|出力|右前輪の回転数(PWM出力)| 
|RightMotorDirPin1|22|出力|右前輪の回転方向(Pin1)|
|RightMotorDirPin2|24|出力|右前輪の回転方向(Pin2)|
|LeftMotorDirPin1|26|出力|左前輪の回転方向(Pin1)|
|LeftMotorDirPin2|28|出力|左前輪の回転方向(Pin2)|
|speedPinL|10|出力|左前輪の回転数(PWM出力)|
|speedPinRB|11|出力|右後輪の回転数(PWM出力)|
|RightMotorDirPin1B|5|出力|右後輪の回転方向(Pin1B)|
|RightMotorDirPin2B|6|出力|右後輪の回転方向(Pin2B)|
|LeftMotorDirPin1B|7|出力|左後輪の回転方向(Pin1B)|
|LeftMotorDirPin2B|8|出力|左後輪の回転方向(Pin2B)|
|speedPinLB|12|出力|左後輪の回転数(PWM出力)|

## モーターの基本動作に対応する関数

* speedで指定する値
  * SPEED 140（通常）   
  * TURN_SPEED 160（回転）
  * speedに0を設定するとモーターは停止する。

### 右側のモータードライバ（Right MODEL-X）での右前輪制御

|関数名|モーターの動作|RightMotorDirPin1|RightMotorDirPin2|speedPinR|
|-----|------------|-----------------|-----------------|--------|
|void FR_fwd(int speed)|右前輪を前進方向|HIGH|LOW|speedの値(アナログ出力)|
|void FR_bck(int speed)|右前輪を後進方向|LOW|HIGH|speedの値(アナログ出力)|
|-|モーターの停止|-|-|0に設定する|

### 右側のモータードライバ（Right MODEL-X）での左前輪制御

|関数名|モーターの動作|LeftMotorDirPin1|LeftMotorDirPin2|speedPinL|
|-----|------------|-----------------|-----------------|--------|
|void FL_fwd(int speed)|左前輪を前進方向|HIGH|LOW|speedの値(アナログ出力)|
|void FL_bck(int speed)|左前輪を後進方向|LOW|HIGH|speedの値(アナログ出力)|
|-|モーターの停止|-|-|0に設定する|

### 左側のモータードライバ（Left MODEL-X)での右後輪制御

|関数名|モーターの動作|RightMotorDirPin1B|RightMotorDirPin2B|speedPinRB|
|-----|------------|-----------------|-----------------|--------|
|void RR_fwd(int speed)|右後輪を前進方向|HIGH|LOW|speedの値(アナログ出力)|
|void RR_bck(int speed)|右後輪を後進方向|LOW|HIGH|speedの値(アナログ出力)|
|-|モーターの停止|-|-|0に設定する|

### 左側のモータードライバ（Left MODEL-X)での左後輪制御

|関数名|モーターの動作|LeftMotorDirPin1B|LeftMotorDirPin2B|speedPinLB|
|-----|------------|-----------------|-----------------|--------|
|void RL_fwd(int speed)|左後輪を前進方向|HIGH|LOW|speedの値(アナログ出力)|
|void RL_bck(int speed)|左後輪を後進方向|LOW|HIGH|speedの値(アナログ出力)|
|-|モーターの停止|-|-|0に設定する|

### 全てのモーターを停止

|関数名|モーターの動作|speedPinLB|speedPinRB|speedPinL|speedPinR|
|-----|------------|----|----|----|---|
|void stop_Stop()|モーターの停止|0|0|0|0|

## ロボット本体の動きを行うための関数

* ロボット本体の動きは、これまであげたモーターの基本動作に対応する関数を組み合わせることで実現する。
* 同じ車輪に対して前進と後進を同時に指定しないようになっている点がポイント。
* 左右シフトを使って斜めに動かす場合は各車輪のスピードを変える必要があるので、すべての車輪の速度を個別に指定できるようになっている。

|関数名|ロボットの動作|左後輪を前進 RL_fwd()|右後輪を前進 RR_fwd()|右前輪を前進FR_fwd()|左前輪を前進 FL_fwd()|左後輪を後進 RL_bck()|右後輪を後進 RR_bck()|右前輪を後進 FR_bck()|左前輪を後進 FL_bck()|
|-----|------------|----|-----|-----|----|----|----|-----|----|
|void go_advance(int speed)|前進|speed|speed|speed|speed|-|-|-|-|
|void go_back(int speed)|後進|-|-|-|-|speed|speed|speed|speed|
|void right_shift(int speed_fl_fwd,int speed_rl_bck ,int speed_rr_fwd,int speed_fr_bck)|右シフト|-| speed_rr_fwd|-| speed_fl_fwd|speed_rl_bck|-|speed_fr_bck|
|void left_shift(int speed_fl_bck,int speed_rl_fwd,int speed_rr_bck,int speed_fr_fwd)|左シフト|speed_rl_fwd|-|speed_fr_fwd|-|-|speed_rr_bck|-|speed_fl_bck|
|void left_turn(int speed)|左前進|-|speed|-|speed|0|-|0|-|
|void right_turn(int speed)|右前進|speed|-|speed|-|-|0|-|0|
|void left_back(int speed)|左後退|0|-|0|-|-|speed|-|speed| 
|void right_back(int speed)|右後退|-|0|-|0|speed|-|speed|-|
|void clockwise(int speed)|時計回り|speed|-|-|speed|-|speed|speed|-|
|void countclockwise(int speed)|反時計回り|-|speed|speed|-|speed|-|-|speed|

## Lesson1の一連の動きを行う関数

* 一連の動きは setup() 関数で行う。この関数はArduinoのプログラムを動かした時に最初に一度だけ呼ばれる関数

### void setup()の内容

|ステップ|関数名|動作内容|
|-|----|-----|
|1|init_GPIO()|Arduinoのピン出力設定を行う。|
|2|go_advance(SPEED)|前進|
|3|delay(1000)|1秒待つ。1秒=1000ミリ秒|
|4|stop_Stop()|モーターを停止|
|5|delay(1000)|1秒待つ|
|6|go_back(SPEED)|後進|
|7|delay(1000)|1秒待つ|
|8|stop_Stop()|モーターを停止|
|9|delay(1000)|1秒待つ|
|10|left_turn(TURN_SPEED)|左前進|
|11|delay(1000)|1秒待つ|
|12|stop_Stop()|モーターを停止|
|13|delay(1000)|1秒待つ|
|14|right_turn(TURN_SPEED)|右前進|
|15|delay(1000)|1秒待つ|
|16|stop_Stop()|モーターを停止|
|17|delay(1000)|1秒待つ|
|18|right_shift(200,200,200,200)|右真横移動|
|19|delay(1000)|1秒待つ|
|20|stop_Stop()|モーターを停止|
|21|delay(1000)|1秒待つ|
|22|left_shift(200,200,200,200)|左真横移動|
|23|delay(1000)|1秒待つ|
|24|stop_Stop()|モーターを停止|
|25|delay(1000)|1秒待つ|
|26|left_shift(200,0,200,0)|左斜め後進|
|27|delay(1000)|1秒待つ|
|28|stop_Stop()|モーターを停止|
|29|delay(1000)|1秒待つ|
|30|right_shift(200,0,200,0)|右斜め前進|
|31|delay(1000)|1秒待つ|
|32|stop_Stop()|モーターを停止|
|33|delay(1000)|1秒待つ|
|34|left_shift(0,200,0,200)|左斜め前進|
|35|delay(1000)|1秒待つ|
|36|stop_Stop()|モーターを停止|
|37|delay(1000)|1秒待つ|
|38|right_shift(0,200,0,200)|右斜め後進|
|39|delay(1000)|1秒待つ|
|40|stop_Stop()|モーターを停止|
|41|delay(1000)|1秒待つ|

