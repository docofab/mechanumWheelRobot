# Lesson3

## 目的とする動作

* ライントレース用のセンサーを使用して、ロボットカーが線に沿って移動するようにします。

## ソースコード

* [metal-2560-lesson3.ino](/Arduino/osoyoo/metal-2560-lesson3/metal-2560-lesson3.ino)

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

## void tracking()

* 各センサーの値を読み取り、２進数の文字列に変換する。

|線の状態|センサー値|ロボットの動作|呼び出されるモーター制御関数|
|---|---|---|---|
|■□□|100|左にシフト|sharpLeftTurn(LOW_SPEED,MID_SPEED)|
|■■□|110|少し左にシフト|forward(0,HIGH_SPEED)|
|□■□,■□■|010,101|前進|forward(MID_SPEED,MID_SPEED)|
|□■■|011|少し右にシフト|forward(HIGH_SPEED,0)|
|□□■|001|右にシフト|sharpRightTurn(MID_SPEED,LOW_SPEED)|
|□□□|000|線を見失った|reverse(MID_SPEED)|
|■■■|111|右に急ターン|sharpRightTurn(MID_SPEED,MID_SPEED)|

