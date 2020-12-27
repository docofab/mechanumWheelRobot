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

## 周囲を見渡す関数

### String watchsurrounding()

周囲の距離を測定し、それらをcm単位で変数に代入し、障害物ステータスを生成します。

|距離が代入される変数名|計測方向|障害物ステータス|センサーの方向(サーボモーターの角度)|
|------------------|-------|-------------|------------------------------|
|centerscanval|正面| XX1XX | 90° |
|ldiagonalscanval|左斜め前| X1XXX | 120° |
|leftscanval|左側| 1XXXX | 170° (180°までサーボが動かなかったため) |
|rightscanval|右側| XXXX1 | 0° |
|rdiagonalscanval|右斜め前| XXX1X | 40° |

* 障害物と判断する閾値
  * const int distancelimit = 30; // 前方の障害物までの最小距離（cm）           
  * const int sidedistancelimit = 30; // 両側の障害物までの最小距離（cm）


* 障害物ステータス
  * 障害物ステータスは2進数で、各ビットが障害物のある方向を示します。（５ビットなので５方向）
  * たとえば、B101000の最後の5桁は01000です。これは、左斜め前に障害物があることを表し、B100111は正面、右斜め前、右横を意味します。
  * 処理中でステータスの初期値をB100000と6桁にしているのは、前5桁をゼロ詰めするためと思われます。

(例)
```
  01000

    0  
  1   0
0       0

  00111

    1
  0   1
0       1
```

## 障害物を自動で回避する関数

### void auto_avoidance()

* const int turntime = 250; //Time the robot spends turning (miliseconds)
* const int backtime = 300; //Time the robot spends turning (miliseconds)
