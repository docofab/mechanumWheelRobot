# Lesson3

## 目的とする動作

* ライントレース用のセンサーを使用して、ロボットカーが線に沿って移動するようにします。

## ソースコード

* [metal-2560-lesson3-reverse.ino](/Arduino/osoyoo/metal-2560-lesson3-reverse/metal-2560-lesson3-reverse.ino)

## Lesson3で追加するハードウェア

* 3-Point Tracking sensor （別売されていないようです。）

## Arduinoで使用する入出力ピン

* 入出力ピンの初期化は void init_GPIO() 関数で行っています。

|定数名|Arduinoピン番号|信号の向き|役割|
|--------|--------------|--------|---|
|sensor1|2|INPUT|左側センサー|
|sensor2|3|INPUT|中央センサー|
|sensor3|4|INPUT|右側センサー|

※モーター制御系はこれまでのLesson1,2と同じなので省略。

## Arduinoのスケッチ

* 参考：[Arduinoライブラリの仕様](http://www.musashinodenpa.com/arduino/ref/index.php)

### void tracking()

* 各センサーの値を読み取り、２進数の文字列に変換する。

```
  String senstr="";                 // 文字列変数の初期化
  int s0 = digitalRead(sensor1);    // digitalReadなので0か1かを光センサーから読み取る。
  int s1 = digitalRead(sensor2);
  int s2 = digitalRead(sensor3);
 
                                // 全ての組み合わせで処理できるように各センサーの値を2進数に変換する。
  int sensorvalue=8;            // 2^3ビット目を常に1にする。 
  sensorvalue +=s0*4+s1*2+s2;   // sensor1*2^2ビット目 + sensor2*2^1ビット目 + sensor3*2^0ビット目 

  senstr= String(sensorvalue,BIN); // sensorvalueを2進数として文字列に変換。
  senstr=senstr.substring(1,4);    // 2文字めから4文字めまで文字列を切り出す。
```

* 使用している主なArduinoライブラリ
    * [digitalRead(sensor1)](http://www.musashinodenpa.com/arduino/ref/index.php?f=0&pos=2075)
    * [String(sensorvalue,BIN)](http://www.musashinodenpa.com/arduino/ref/index.php?f=0&pos=1418)
    * [senstr.substring(1,4)](http://www.musashinodenpa.com/arduino/ref/index.php?f=0&pos=1462)


* 2進数の文字列にしたがってモーターを動かす。

|線の状態|センサー値|ロボットの動作|呼び出されるモーター制御関数|
|---|---|---|---|
|■□□|100|左にシフト|sharpLeftTurn(LOW_SPEED,MID_SPEED)|
|■■□|110|少し左にシフト|forward(0,HIGH_SPEED)|
|□■□,■□■|010,101|前進|forward(MID_SPEED,MID_SPEED)|
|□■■|011|少し右にシフト|forward(HIGH_SPEED,0)|
|□□■|001|右にシフト|sharpRightTurn(MID_SPEED,LOW_SPEED)|
|□□□|000|線を見失った|reverse(MID_SPEED)|
|■■■|111|右に急ターン|sharpRightTurn(MID_SPEED,MID_SPEED)|

## void loop()

* tracking();を繰り返し実行する。

