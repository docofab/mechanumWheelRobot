# Lesson5

## 目的とする動作

* WiFi制御で移動するようにします。
* 接続方式によってAPモードとSTAモードがあります。

## ソースコード

* [metal-2560-lesson5A.ino](/Arduino/osoyoo/metal-2560-lesson5-reverse/metal-2560-lesson5A/metal-2560-lesson5A.ino)　APモード
* [metal-2560-lesson5B.ino](/Arduino/osoyoo/metal-2560-lesson5-reverse/metal-2560-lesson5B/metal-2560-lesson5B.ino)　STAモード

## 追加するハードウェア

* OSOYOO V1.0 Wifi Shield

## スマホアプリ

* OSOYOO Wifi UDP Robot Car Controller 

## Arduinoで使用する入出力ピン

* 入出力ピンの初期化は void init_GPIO() 関数で行っています。

|定数名|Arduinoピン番号|Arduinoから見た信号の向き|Wifi-Board|
|--------|--------------|--------|---|
|(Serial1)|D19(RX1)|INPUT|E_TX|
|(Serial1)|D18(TX1)|OUTPUT|E_RX|

Arduino Megaでは4つのシリアルポート(Serial, Serial1, Serial2, Serial3)があります。

※モーター制御系はこれまでのLesson1,2と同じなので省略。

