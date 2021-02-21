# Lesson4

## 目的とする動作

* Bluetooth制御で移動するようにします。

## ソースコード

* [metal-2560-lesson4-reverse.ino](/Arduino/osoyoo/metal-2560-lesson4-reverse/metal-2560-lesson4-reverse.ino)

## Lesson4で追加するハードウェア

* OSOYOO V1.0 Wifi Shield
* OSOYOO HC02 bluetooth module

## スマホアプリ

* OSOYOO imitation driving


## Arduinoで使用する入出力ピン

* 入出力ピンの初期化は void init_GPIO() 関数で行っています。

|定数名|Arduinoピン番号|Arduinoから見た信号の向き|Wifi-Board|
|--------|--------------|--------|---|
|(Serial1)|D19(RX1)|INPUT|B_TX|
|(Serial1)|D18(TX1)|OUTPUT|B_RX|

Arduino Megaでは4つのシリアルポート(Serial, Serial1, Serial2, Serial3)があります。

※モーター制御系はこれまでのLesson1,2と同じなので省略。


## void setup()
```
Serial.begin(9600);//In order to fit the Bluetooth module's default baud rate, only 9600
Serial1.begin(9600);
```

## void loop()
```
{
 do_Uart_Tick();
}
```

## void do_Uart_Tick()
```


```

|Uart_Date|ロボットの動作|呼び出されるモーター制御関数|
|---|---|---|
|M| |go_advance(110,110) go_advance(move_speed,move_speed);|
|L| |go_advance(SLOW_TURN_SPEED,TURN_SPEED) else left_turn(SLOW_TURN_SPEED)|
|R| |go_advance(TURN_SPEED,SLOW_TURN_SPEED) else right_turn(SLOW_TURN_SPEED);|
|B| |go_back(BACK_SPEED,BACK_SPEED)|
|X| |go_back(SLOW_TURN_SPEED,TURN_SPEED) else left_back(TURN_SPEED) |
|Y| |go_back(TURN_SPEED,SLOW_TURN_SPEED) else right_back(TURN_SPEED)|
|F|left shift|left_shift(180,170,190,190)|
|J|right shift|right_shift(200,170,170,200)|
|G|left ahead or left back|left_shift(0,150,0,150) else left_shift(150,0,150,0)|
|I|right ahead or right back|right_shift(180,0,150,0) else right_shift(0,130,0,130)|
|E|停止|stop_stop()|


## car_status get_status( char buffUART[])
