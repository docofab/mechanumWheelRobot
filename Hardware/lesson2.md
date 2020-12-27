# Lesson2

## 目的とする動作

* 超音波距離センサーを使用して、ロボットカーが障害物を回避するようにします。

## ソースコード

* [metal-2560-lesson2.ino](/Arduino/metal-2560-lesson2/metal-2560-lesson2.ino)

## Arduinoで使用する出力ピン

* 出力ピンの初期化は void setup() 関数で行っています。

|定数名|Arduinoピン番号|信号の向き|役割|
|--------|--------------|--------|---|
|Trig_PIN|30|OUTPUT|HC-SR04のトリガ(A4)|
|Echo_PIN|31|INPUT|HC-SR04のエコー(A5)|
|SERVO_PIN|13|OUTPUT|サーボモーター(D5)|

## Lesson2で追加するハードウェア

* [超音波距離センサー HC-SR04](https://akizukidenshi.com/catalog/g/gM-11009/)
  * データシートの7. ModuleTimingを参照
     1. トリガ端子に最低10マイクロ秒のパルス信号を送る。
     1. 40KHzのバースト信号が送信される。
     1. 送信直後にECHO端子がHIGHになり、反射したバースト信号が戻ってくるタイミングでLOWになる。
     1. 距離はECHO端子のパルス幅のマイクロ秒/58の値がcmになる。
* サーボモーター 同等品：[マイクロサーボ9g SG-90](https://akizukidenshi.com/catalog/g/gM-08761/)  
  * 以下のArduino標準ライブラリを使用して制御する。
    * [Servoライブラリ](https://www.arduino.cc/reference/en/libraries/servo/)

## 超音波センサーで障害物までの距離を図る関数

* ソース中の 0.01657はおよそ1/60。データシートの値とやや食い違いがある。1/58=0.01724

```
/*detection of ultrasonic distance*/
int watch(){
  long echo_distance;

  /* TRIGパルスを作る
        --------
   5ms |  15ms  |
  -----         --------- */
  digitalWrite(Trig_PIN,LOW);    // TRIGをLOWにする  
  delayMicroseconds(5);          // 5ms待つ                                                                    
  digitalWrite(Trig_PIN,HIGH);   // TRIGをHIGHにする
  delayMicroseconds(15);         // 15ms待つ
  digitalWrite(Trig_PIN,LOW);    // TRIGをLOWにする

  /* ECHOパルス幅を取得する */
  echo_distance=pulseIn(Echo_PIN,HIGH); // unsigned long pulseIn()：信号がHIGHとなっている時間をマイクロ秒で返します
  
  echo_distance=echo_distance*0.01657; //how far away is the object in cm
 
//Serial.println((int)echo_distance);  //デバック用。コメントをはすずと距離の値がシリアル出力される。
 
  /* 距離の値を返す */
  return round(echo_distance);   /* round()は四捨五入する関数 */
}
```

